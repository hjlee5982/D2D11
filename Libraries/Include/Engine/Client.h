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
public:
	static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
private:
	void ClientInitialize();
private:
	void EngineInitialize();
	void UpdateSingleThread();
	void UpdateMultiThread();
	void FixedUpdate();
	void Render();
private:
	void Destroy();


	// 멀티스레딩
private:
	void UpdateThread();
	void RenderThread();
private:
	std::thread updateThread;
	std::thread renderThread;
private:
	std::mutex mtx;
	std::condition_variable cvUpdateDone;
	std::condition_variable cvRenderDone;
private:
	bool updateDone = false;
	bool renderDone = true;
	bool running = true;

private:
	i32 ThreadIdx = 1;

private:
	std::chrono::steady_clock::time_point _t0;
	std::chrono::steady_clock::time_point _t1;
	std::chrono::steady_clock::time_point _t2;
	std::chrono::steady_clock::time_point _t3;

	f64 _ms1;
	f64 _ms2;
};
