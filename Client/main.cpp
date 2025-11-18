#include "pch.h"
#include "MainScene.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	AllocConsole();

	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);
	freopen_s(&fp, "CONIN$", "r", stdin);

	ClientOption option;
	{
		option.hInstance  = hInstance;
		option.vsync      = false;
		option.clearColor = Color(Colors::Blue);

		option.appName  = L"FlappyBird";
		option.width    = 700;
		option.height   = 1000;
		option.windowed = false;
	}
	Global::ClientOption = option;

	sptr<MainScene> scene = makeSptr<MainScene>("MainScene");

	SCENE.AddScene(scene);
	CLIENT.Awake();

	FreeConsole();

	return 0;
}