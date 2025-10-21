#include "pch.h"
#include "FlappyBird.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	ClientOption option;
	{
		option.hInstance = hInstance;
		option.vsync = false;
		option.clearColor = Color(Colors::Blue);

		option.appName  = L"FlappyBird";
		option.width    = 750;
		option.height   = 1000;
		option.windowed = false;

		option.app = makeSptr<FlappyBird>();
	}
	Client::Instance().Run(option);

	return 0;
}