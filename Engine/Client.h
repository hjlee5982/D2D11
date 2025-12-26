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
	void ClientInitialize();
	void EngineInitialize();
private:
	void UpdateSingleThread();
	void UpdateMultiThread();
	void UpdateMultiSemThread();
public:
	static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);


	// 멀티스레딩 ( 뮤텍스 )
private:
	void RenderThread();
private:
	std::thread renderThread;
private:
	std::mutex mtx;
	std::condition_variable cvRender;
private:
	bool renderReady = true;
	bool running = true;


	// 멀티스레딩 ( 세마포어 )
private:
	std::binary_semaphore semRenderReady{ 0 };
	std::atomic<bool> aRunning = true;
private:
	std::thread renderSemThread;
private:
	void UpdateSemRender();

private:
	i32 ThreadIdx = 2;

private:
	std::chrono::steady_clock::time_point _t0;
	std::chrono::steady_clock::time_point _t1;
	std::chrono::steady_clock::time_point _t2;
	std::chrono::steady_clock::time_point _t3;

	f64 _ms1;
	f64 _ms2;
};
