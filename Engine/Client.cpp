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
	updateThread = std::thread(&Client::UpdateThread, this);
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
			{
				std::lock_guard<std::mutex> lock(mtx);
				running = false;
				cvUpdateDone.notify_all();
				cvRenderDone.notify_all();
			}
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

		{
			std::lock_guard<std::mutex> lock(mtx);
			updateDone = true;
			cvUpdateDone.notify_one();
		}
		{
			std::unique_lock<std::mutex> lock(mtx);
			cvRenderDone.wait(lock, [&] {return renderDone || !running; });
			if (!running)
			{
				break;
			}
			renderDone = false;
			std::cout << _ms1 + _ms2 << std::endl;
		}
	}

	SCENE.SaveScene();
	SOUND.Destroy();

	cvUpdateDone.notify_all();
	cvRenderDone.notify_all();

	updateThread.join();
	renderThread.join();
}

void Client::UpdateThread()
{
	while (running)
	{
		// 1) 렌더 스레드가 렌더를 끝낼 때까지 대기
		{
			std::unique_lock<std::mutex> lock(mtx);
			cvRenderDone.wait(lock, [&] { return renderDone || !running; });

			if (!running)
			{
				break;
			}

			renderDone = false;
		}

		_t0 = std::chrono::high_resolution_clock::now();

		// 2) 업데이트 실행
		GAMEOBJECT.Update();
		GAMEOBJECT.LateUpdate();

		// 3) 렌더링 데이터 생성
		RENDERER.CollectRenderData();
		RENDERER.SwapContext();

		_t1 = std::chrono::high_resolution_clock::now();

		_ms1 = std::chrono::duration<f64, std::milli>(_t1 - _t0).count();

		// 4) 업데이트 완료 알림
		std::lock_guard<std::mutex> lock(mtx);
		updateDone = true;
		cvUpdateDone.notify_one();
	}
}

void Client::RenderThread()
{
	while (running)
	{
		// 1) 업데이트 완료 대기
		{
			std::unique_lock<std::mutex> lock(mtx);
			cvUpdateDone.wait(lock, [&] { return updateDone || !running; });

			if (!running)
			{
				break;
			}

			updateDone = false;
		}
		_t2 = std::chrono::high_resolution_clock::now();

		// 2) 렌더링
		DIRECTX.RenderBegin();
		RENDERER.RenderGameObject();
		DIRECTX.RenderEnd();
		_t3 = std::chrono::high_resolution_clock::now();

		_ms2 = std::chrono::duration<f64, std::milli>(_t3 - _t2).count();

		// 3) 렌더 완료 알림
		{
			std::lock_guard<std::mutex> lock(mtx);
			renderDone = true;
		}
		cvRenderDone.notify_one();
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


