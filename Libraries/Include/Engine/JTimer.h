#pragma once

class JTimer
{
public:
	void Initialize();
public:
	void Update();
public:
	f64 _deltaTime = 0.f;
	LARGE_INTEGER _cpuTick = {};
	LARGE_INTEGER _begin = {};
	LARGE_INTEGER _end = {};
};

