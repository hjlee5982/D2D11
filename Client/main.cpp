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
		option.hInstance = hInstance;
		option.vsync = false;
		option.clearColor = Color(Colors::Gray);

		option.appName  = L"FlappyBird";
		option.width    = 600;
		option.height   = 800;
		option.windowed = false;

		option.scene = makeSptr<MainScene>("MainScene");
	}

	Global::ClientOption = option;

	CLIENT.Awake();

	FreeConsole();

	return 0;
}

//int main()
//{
//#ifdef _DEBUG
//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//#endif
//
//	ClientOption option;
//	{
//		option.hInstance = GetModuleHandle(NULL);
//		option.vsync = false;
//		option.clearColor = Color(Colors::Gray);
//
//		option.appName = L"FlappyBird";
//		option.width = 600;
//		option.height = 800;
//		option.windowed = false;
//
//		option.scene = makeSptr<FlappyBird>();
//	}
//
//	Global::ClientOption = option;
//
//	CLIENT.Awake();
//
//	return 0;
//}