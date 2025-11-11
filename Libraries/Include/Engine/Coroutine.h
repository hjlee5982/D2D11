#pragma once

struct WaitForSeconds
{
	float seconds;

	bool await_ready() const noexcept
	{
		return false;
	}

	void await_suspend(std::coroutine_handle<> handle) const
	{
		std::thread([handle, sec = seconds]()
			{
				std::this_thread::sleep_for(std::chrono::duration<float>(sec));
			}).detach();
	}

	void await_resume() const noexcept {}
};

struct Task
{
	struct promise_type
	{
		Task get_return_object() { return {}; }
		std::suspend_never initial_suspend() noexcept { return {}; }
		std::suspend_never final_suspend() noexcept { return {}; }
		void return_void() noexcept {}
		void unhandled_exception() { std::terminate(); }
	};
};
