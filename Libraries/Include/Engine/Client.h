#pragma once

struct ClientOption
{
	HWND      hWnd;

	HINSTANCE hInstance;
	bool      vsync;
	Color     clearColor;

	wstring   appName;
	f32       width;
	f32       height;
	bool      windowed;
};

class Client : public Singleton<Client>
{
public:
	virtual void Awake() override;
private:
	WPARAM Run();
public:
	static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
private:
	void Initialize();
	void Update();
	void FixedUpdate();
	void Render();
private:
	void Destroy();
};
