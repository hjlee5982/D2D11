#include "pch.h"
#include "Client.h"
#include "IScene.h"
#include "Renderer.h"
#include "AssetManager.h"
#include "GameObjectManager.h"
#include "CollisionManager.h"

void Client::Initialize()
{
	Timer            ::Instance().Awake();
	Device           ::Instance().Awake();
	AssetManager     ::Instance().Awake();
	Renderer         ::Instance().Awake();

	Global::ClientOption.scene->InitializeScene();

	GameObjectManager::Instance().Awake();
	GameObjectManager::Instance().Start();
}

void Client::Update()
{
	Device::Instance().RenderBegin();
	{
		Timer::Instance().Update();

		CollisionManager::Instance().Update();
		GameObjectManager::Instance().Update();
		GameObjectManager::Instance().LateUpdate();

		Renderer::Instance().Render();
	}
	Device::Instance().RenderEnd();
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

	while (msg.message != WM_QUIT)
	{
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		Update();
	}

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