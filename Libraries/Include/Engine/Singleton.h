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

#define DEVICE  Device::Instance().GetDevice()
#define CONTEXT Device::Instance().GetContext()

#define CLIENT     Client::Instance()
#define GAMEOBJECT GameObjectManager::Instace()
#define ASSET      AssetManager::Instance()
#define RENDERER   Renderer::Instance()
#define COLLISION  CollisionManager::Instance()
#define TIMER      Timer::Instance()