#include "pch.h"
#include "FlappyBird.h"
#include<iostream>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// AllocConsole();

	// 표준 입출력 스트림을 콘솔에 연결
	/*FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);
	freopen_s(&fp, "CONIN$", "r", stdin);

	std::cout << "콘솔 로그 테스트" << std::endl;*/

#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	ClientOption option;
	{
		option.hInstance = hInstance;
		option.vsync = false;
		option.clearColor = Color(Colors::Gray);

		option.appName  = L"FlappyBird";
		option.width    = 600;
		option.height   = 800;
		option.windowed = false;

		option.scene = makeSptr<FlappyBird>();
	}

	Global::ClientOption = option;

	CLIENT.Awake();

	//FreeConsole();

	return 0;
}