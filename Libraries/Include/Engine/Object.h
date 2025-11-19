#pragma once



class Object abstract : public IJson
{
public:
	virtual const uint64_t  GetType() const { return 0; };
	virtual const char* GetTypeName() const { return nullptr; };
public:
	virtual void OnCollisionEnter2D(sptr<class BoxCollider2D> collider) {};
public:
	const string& GetName();
public:
	string name = "none";
	string tag = "none";
	bool isActive = true;
};

#include "GameObject.h"
#include "UIObject.h"
#include "GameObjectManager.h"
#include "UIManager.h"

template<typename T, typename... Args>
static sptr<T> Instantiate(Args&&... args)
{
	sptr<T> go = makeSptr<T>();

	if constexpr (std::is_same_v<T, GameObject>)
	{
		go->transform = go->AddComponent<Transform>(std::forward<Args>(args)...);
		GAMEOBJECT.AddGameObject(go);

	}
	else if (std::is_same_v<T, UIObject>)
	{

	}


	return go;
}