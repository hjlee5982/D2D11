#include "pch.h"
#include "Timer.h"

void Timer::Awake()
{
	_timePoint = std::chrono::steady_clock::now();
}

void Timer::Update()
{
    auto now = std::chrono::steady_clock::now();

    std::chrono::duration<f64> sec = now - _timePoint;

    _deltaTime = sec.count();

    _timePoint = now;
}
