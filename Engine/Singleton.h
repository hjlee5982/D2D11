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

#define DIRECTX Device::Instance()
#define DEVICE  Device::Instance().GetDevice()
#define CONTEXT Device::Instance().GetContext()

#define ASSET      AssetManager     ::Instance()
#define TIMER      Timer            ::Instance()
#define INPUT      InputSystem      ::Instance()
#define CLIENT     Client           ::Instance()
#define RENDERER   Renderer         ::Instance()
#define COLLISION  CollisionManager ::Instance()
#define GAMEOBJECT GameObjectManager::Instance()