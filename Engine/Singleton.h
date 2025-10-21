#pragma once

template<typename T>
class Singleton abstract
{
protected:
	Singleton() {}
	Singleton(const Singleton&) = delete;
	Singleton& operator = (const Singleton&) = delete;
public:
	virtual ~Singleton() = default;
public:
	virtual void Awake() = 0;
public:
	static T& Instance()
	{
		static T instance;
		return instance;
	}
};

