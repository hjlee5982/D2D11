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

#include "DebugTimer.h"



void Client::Awake()
{
	// Win32 초기화
	ClientInitialize();

	// 엔진 초기화
	EngineInitialize();

	UHT();

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
		//TimeMeasurement totalFrameTimer;

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

		//TimeMeasurement cpuWorkTimer;

		TIMER.Update();
		INPUT.Update();
		SOUND.Update();

		GAMEOBJECT.Update();
		GAMEOBJECT.LateUpdate();

		RENDERER.CollectRenderData();
		RENDERER.SwapContext();

		//f64 cpuWorkDuration = cpuWorkTimer.GetDurationUs();
		//stCumulativeCpuWorkTime += cpuWorkDuration; // 누적

		DIRECTX.RenderBegin();
		RENDERER.RenderGameObject();
		DIRECTX.RenderEnd();

		////  프레임 종료 시간 측정 및 누적 (ST_TotalFrame)
		//f64 totalFrameDuration = totalFrameTimer.GetDurationUs();
		//stCumulativeTotalFrameTime += totalFrameDuration; // 누적
		//stFrameCount++;

		//// =========================================================
		//// 3. 통계 출력 로직 (1초마다)
		//auto now = std::chrono::high_resolution_clock::now();
		//f64 elapsedSec = std::chrono::duration_cast<std::chrono::duration<f64>>(now - lastLogTime).count();

		//if (elapsedSec >= LOG_INTERVAL_SEC)
		//{
		//	std::lock_guard<std::mutex> lock(g_log_mutex); // 출력 뮤텍스 사용

		//	f64 avgTotalFrame = stCumulativeTotalFrameTime / stFrameCount;
		//	f64 avgCpuWork = stCumulativeCpuWorkTime / stFrameCount;
		//	f64 avgFPS = 1.0 / (avgTotalFrame / 1000000.0); // us를 초로 변환

		//	std::cout << "[ST STATS] Frames: " << stFrameCount
		//		<< " | Avg FPS: " << std::fixed << std::setprecision(2) << avgFPS
		//		<< " | Avg Total Time: " << avgTotalFrame << " us"
		//		<< " | Avg CPU Work Time: " << avgCpuWork << " us" << std::endl;

		//	// 리셋
		//	stCumulativeTotalFrameTime = 0.0;
		//	stCumulativeCpuWorkTime = 0.0;
		//	stFrameCount = 0;
		//	lastLogTime = now;
		//}
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
		//TimeMeasurement totalFrameTimer;


		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT)
		{
			aRunning = false;
			semBufferFreeSignal.release();
			semRenderReadySignal.release();
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

		//TimeMeasurement cpuWaitTimer;
		semBufferFreeSignal.acquire();
		//f64 cpuWaitDuration = cpuWaitTimer.GetDurationUs();
		//cumulativeCpuWaitTime += cpuWaitDuration;

		RENDERER.CollectRenderData();

		std::lock_guard<std::mutex> lock(mtx);
		RENDERER.SwapTripleContext();

		semRenderReadySignal.release();


		//f64 totalFrameDuration = totalFrameTimer.GetDurationUs();
		//cumulativeTotalFrameTime += totalFrameDuration;
		//frameCount++;


		//auto now = std::chrono::high_resolution_clock::now();
		//f64 elapsedSec = std::chrono::duration_cast<std::chrono::duration<f64>>(now - lastLogTime).count();

		//if (elapsedSec >= LOG_INTERVAL_SEC)
		//{
		//	std::lock_guard<std::mutex> lock(g_log_mutex);

		//	f64 avgCpuWait = cumulativeCpuWaitTime / frameCount;
		//	f64 avgTotalFrame = cumulativeTotalFrameTime / frameCount;
		//	f64 avgFPS = 1.0 / (avgTotalFrame / 1000000.0);

		//	std::cout << "[MT STATS] Frames: " << frameCount
		//		<< " | Avg FPS: " << std::fixed << std::setprecision(2) << avgFPS
		//		<< " | Avg Total Time: " << avgTotalFrame << " us"
		//		<< " | Avg CPU Wait: " << avgCpuWait << " us" << std::endl;

		//	// 리셋
		//	cumulativeCpuWaitTime = 0.0;
		//	cumulativeTotalFrameTime = 0.0;
		//	frameCount = 0;
		//	lastLogTime = now;
		//}
	}

	SCENE.SaveScene();
	SOUND.Destroy();

	semBufferFreeSignal.release();
	semRenderReadySignal.release();

	renderThread.join();
}

void Client::RenderThread()
{
	while (aRunning.load())
	{
		semRenderReadySignal.acquire();

		if (!aRunning.load()) break;

		DIRECTX.RenderBegin();
		RENDERER.RenderGameObject();
		DIRECTX.RenderEnd();

		semBufferFreeSignal.release();
	}
}

#include "TypeRegistry.h"
#include "TestTransform.h"
#include "TestCamera.h"
#include "TestController.h"
#include "TestScene.h"

void Client::UHT()
{
	auto a = makeUptr<TestTransform>();
	auto b = makeUptr<TestCamera>();
	auto c = makeUptr<TestController>();

	auto saveScene = makeUptr<TestScene>();
	{
		auto camera = saveScene->CreateObject();
		{
			camera->AddComponent1("TestTransform");
			camera->AddComponent1("TestCamera");
		}
		auto player = saveScene->CreateObject();
		{
			player->AddComponent1("TestTransform");
			player->AddComponent1("TestController");
		}
	}
	saveScene->Save("scene.json");

	auto loadScene = makeUptr<TestScene>();
	loadScene->Load("scene.json");
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


