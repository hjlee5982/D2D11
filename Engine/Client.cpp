#include "pch.h"
#include "Client.h"
#include "Scene.h"
#include "RenderManager.h"
#include "AssetManager.h"
#include "GameObjectManager.h"
#include "CollisionManager.h"
#include "Log.h"
#include "InputSystem.h"
#include "ObjectFactory.h"
#include "FontManager.h"
#include "SceneManager.h"
#include "SoundManager.h"

void Client::Awake()
{
	// Win32 초기화
	ClientInitialize();

	// 엔진 초기화
	EngineInitialize();

	switch (ThreadIdx)
	{
	case 0:
		UpdateSingleThread();
		break;

	case 1:
		UpdateMultiThread();
		break;

	case 2:
		UpdateMultiSemThread();
		break;
	}
}

void Client::ClientInitialize()
{
	WNDCLASSEXW wcex;
	{
		wcex.cbSize        = sizeof(WNDCLASSEX);
		wcex.style         = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc   = WndProc;
		wcex.cbClsExtra    = 0;
		wcex.cbWndExtra    = 0;
		wcex.hInstance     = Global::ClientOption.hInstance = GetModuleHandle(NULL);
		wcex.hIcon         = ::LoadIcon(NULL, IDI_WINLOGO);
		wcex.hCursor       = ::LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName  = NULL;
		wcex.lpszClassName = Global::ClientOption.appName.c_str();
		wcex.hIconSm       = wcex.hIcon;
	}
	RegisterClassExW(&wcex);

	RECT windowRect = { 0, 0, Global::ClientOption.width, Global::ClientOption.height };
	::AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);

	Global::ClientOption.hWnd = CreateWindowW
	(
		Global::ClientOption.appName.c_str(),
		Global::ClientOption.appName.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr,
		nullptr,
		Global::ClientOption.hInstance,
		nullptr
	);

	if (!Global::ClientOption.hWnd)
	{
		return;
	}

	::ShowWindow(Global::ClientOption.hWnd, SW_SHOWNORMAL);
	::UpdateWindow(Global::ClientOption.hWnd);
}

void Client::EngineInitialize()
{
	LOG     .Awake();
	TIMER   .Awake();
	INPUT   .Awake();
	DIRECTX .Awake();
	ASSET   .Awake();
	FACTORY	.Awake();
	FONT	.Awake();
	RENDERER.Awake();
	SOUND   .Awake();
	SCENE   .Awake();

	GAMEOBJECT.Awake();
	GAMEOBJECT.Start();
}

void Client::UpdateSingleThread()
{
	// FixedUpdate
	f64 acc = 0.f;
	f64 FIXED_DELTA = 1.f / 60.f;

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		acc += TIMER.DeltaTime();

		while (acc >= FIXED_DELTA)
		{
			GAMEOBJECT.FixedUpdate();
			COLLISION.FixedUpate();
			acc = 0.f;
		}

		auto t0 = std::chrono::high_resolution_clock::now();

		TIMER.Update();
		INPUT.Update();
		SOUND.Update();

		GAMEOBJECT.Update();
		GAMEOBJECT.LateUpdate();
		RENDERER.CollectRenderData();
		RENDERER.SwapContext();

		DIRECTX.RenderBegin();
		RENDERER.RenderGameObject();
		DIRECTX.RenderEnd();

		auto t1 = std::chrono::high_resolution_clock::now();

		f64 ms = std::chrono::duration<f64, std::milli>(t1 - t0).count();

		std::cout << ms << std::endl;
	}

	SCENE.SaveScene();
	SOUND.Destroy();
}

void Client::UpdateMultiThread()
{
	// 업데이트, 렌더 스레드 실행
	renderThread = std::thread(&Client::RenderThread, this);

	// FixedUpdate
	f64 acc = 0.f;
	f64 FIXED_DELTA = 1.f / 60.f;

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT)
		{
			std::lock_guard<std::mutex> lock(mtx);
			cvRender.notify_one();
			running = false;

			break;
		}

		acc += TIMER.DeltaTime();

		while (acc >= FIXED_DELTA)
		{
			GAMEOBJECT.FixedUpdate();
			COLLISION.FixedUpate();
			acc = 0.f;
		}

		TIMER.Update();
		INPUT.Update();
		SOUND.Update();

		GAMEOBJECT.Update();
		GAMEOBJECT.LateUpdate();

		RENDERER.CollectRenderData();


		std::lock_guard<std::mutex> lock(mtx);
		RENDERER.SwapContext();

		renderReady = true;

		cvRender.notify_one();
	}

	SCENE.SaveScene();
	SOUND.Destroy();

	cvRender.notify_all();

	renderThread.join();
}

void Client::UpdateMultiSemThread()
{
	// 업데이트, 렌더 스레드 실행
	renderSemThread = std::thread(&Client::UpdateSemRender, this);

	// FixedUpdate
	f64 acc = 0.f;
	f64 FIXED_DELTA = 1.f / 60.f;

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT)
		{
			//std::lock_guard<std::mutex> lock(mtx);
			aRunning = false;
			semRenderReady.release();
		}

		acc += TIMER.DeltaTime();

		while (acc >= FIXED_DELTA)
		{
			GAMEOBJECT.FixedUpdate();
			COLLISION.FixedUpate();
			acc = 0.f;
		}

		TIMER.Update();
		INPUT.Update();
		SOUND.Update();

		GAMEOBJECT.Update();
		GAMEOBJECT.LateUpdate();

		RENDERER.CollectRenderData();

		std::lock_guard<std::mutex> lock(mtx);
		RENDERER.SwapContext();

		semRenderReady.release();
	}

	SCENE.SaveScene();
	SOUND.Destroy();

	semRenderReady.release();

	renderSemThread.join();
}

void Client::RenderThread()
{
	while (running)
	{
		std::unique_lock<std::mutex> lock(mtx);
		cvRender.wait(lock, [&] {return renderReady || !running; });

		if (!running) break;

		renderReady = false;

		lock.unlock();

		DIRECTX.RenderBegin();
		RENDERER.RenderGameObject();
		DIRECTX.RenderEnd();
	}
}

void Client::UpdateSemRender()
{
	while (aRunning)
	{
		semRenderReady.acquire();

		if (!aRunning.load()) break;

		DIRECTX.RenderBegin();
		RENDERER.RenderGameObject();
		DIRECTX.RenderEnd();
	}
}

LRESULT CALLBACK Client::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:

			DestroyWindow(handle);
			break;
		}
		break;

	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return ::DefWindowProc(handle, message, wParam, lParam);
}


