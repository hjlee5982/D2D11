#include "pch.h"
#include "Client.h"
#include "Scene.h"
#include "Renderer.h"
#include "AssetManager.h"
#include "GameObjectManager.h"
#include "CollisionManager.h"

void Client::Initialize()
{
	LOG     .Awake();
	TIMER   .Awake();
	INPUT   .Awake();
	DIRECTX .Awake();
	ASSET   .Awake();
	FACTORY	.Awake();
	RENDERER.Awake();
	SCENE   .Awake();

	// Global::ClientOption.scene->InitializeScene();

	GAMEOBJECT.Awake();
	GAMEOBJECT.Start();
}

void Client::Update()
{
	TIMER.Update();
	INPUT.Update();

	GAMEOBJECT.Update();
	GAMEOBJECT.LateUpdate();
}

void Client::FixedUpdate()
{
	GAMEOBJECT.FixedUpdate();
	COLLISION.FixedUpate();
}

void Client::Render()
{
	DIRECTX.RenderBegin();

	RENDERER.Render();

	DIRECTX.RenderEnd();
}

void Client::Destroy()
{
	SCENE.SaveScene();
}

void Client::Awake()
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

	Run();
}

WPARAM Client::Run()
{
	Initialize();

	MSG msg = { 0 };

	f64 acc = 0.f;
	f64 FIXED_DELTA = 1.f / 60.f;

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
			FixedUpdate();
			acc = 0.f;
		}

		Update();

		Render();
	}

	Destroy();

	return msg.wParam;
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