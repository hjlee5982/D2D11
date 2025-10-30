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
		option.clearColor = Color(Colors::Gray);

		option.appName  = L"FlappyBird";
		option.width    = 600;
		option.height   = 800;
		option.windowed = false;

		option.scene = makeSptr<FlappyBird>();
	}

	Global::ClientOption = option;

	CLIENT.Awake();

	return 0;
}