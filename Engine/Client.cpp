#include "pch.h"
#include "Client.h"
#include "IExecute.h"

void Client::Initialize()
{
	Device::Instance().Awake(_option);

	_option.app->Awake();
	_option.app->Start();
}

void Client::Update()
{
	Device::Instance().RenderBegin();
	{
		_option.app->Update();
		_option.app->LateUpdate();
	}
	Device::Instance().RenderEnd();
}

void Client::Awake()
{
}

WPARAM Client::Run(const ClientOption& option)
{
	_option = option;

	WNDCLASSEXW wcex;
	{
		wcex.cbSize        = sizeof(WNDCLASSEX);
		wcex.style         = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc   = WndProc;
		wcex.cbClsExtra    = 0;
		wcex.cbWndExtra    = 0;
		wcex.hInstance     = _option.hInstance = GetModuleHandle(NULL);
		wcex.hIcon         = ::LoadIcon(NULL, IDI_WINLOGO);
		wcex.hCursor       = ::LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName  = NULL;
		wcex.lpszClassName = _option.appName.c_str();
		wcex.hIconSm = wcex.hIcon;
	}
	RegisterClassExW(&wcex);

	RECT windowRect = { 0, 0, _option.width, _option.height };
	::AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);

	_option.hWnd = CreateWindowW
	(
		_option.appName.c_str(),
		_option.appName.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr,
		nullptr,
		_option.hInstance,
		nullptr
	);

	if (!_option.hWnd)
	{
		return FALSE;
	}

	::ShowWindow(_option.hWnd, SW_SHOWNORMAL);
	::UpdateWindow(_option.hWnd);

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