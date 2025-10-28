#include "pch.h"
#include "Timer.h"

void Timer::Awake()
{
	_timePoint = std::chrono::steady_clock::now();
}

void Timer::Update()
{
	std::chrono::duration<f32> sec = std::chrono::steady_clock::now() - _timePoint;

	_deltaTime = sec.count();

	if (_deltaTime >= 0.0f)
	{
		_totalTime += _deltaTime;

		++_frameCount;

		_elapsed += _deltaTime;

		if (_elapsed >= 1.0f)
		{
			_FPS        = _frameCount;
			_frameCount = 0;
			_elapsed    = 0.0f;
		}
	}

	_timePoint = std::chrono::steady_clock::now();
}
