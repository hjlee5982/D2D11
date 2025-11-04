#pragma once

#include "GameObjectManager.h"

class GameObject : public Object, public std::enable_shared_from_this<GameObject>
{
public:
	virtual ~GameObject() = default;
public:
	virtual void OnCollisionEnter(sptr<class BoxCollider2D> collider) override;
public:
	template<typename T, typename ...Args>
	sptr<T> AddComponent(Args&& ... args)
	{
		static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");

		auto idx = std::type_index(typeid(T));
		
		if (_components.find(idx) == _components.end())
		{
			sptr<T> component = makeSptr<T>(args...);

			component->SetOwner(shared_from_this());

			// 컴포넌트 어웨이크 전에 초기화가 필요한 경우
			// ex) 기본 머티리얼이나 기본 매시 생성해줘야 하는 컴포넌트들이 필요
			component->Init();

			_components.emplace(idx, component);

			return component;
		}

		return GetComponent<T>();
	}
public:
	template<typename T, typename ...Args>
	sptr<T> GetComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");

		auto it = _components.find(std::type_index(typeid(T)));

		if (it != _components.end())
		{
			return std::static_pointer_cast<T>(it->second);
		}
		
		return nullptr;
	}
public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
private:
	Dictionary<std::type_index, sptr<class Component>> _components;
public:
	sptr<class Transform> transform;
};

template<typename... Args>
static sptr<GameObject> Instantiate(Args&&... args)
{
	sptr<GameObject> go = makeSptr<GameObject>();

	go->transform = go->AddComponent<Transform>(std::forward<Args>(args)...);

	GAMEOBJECT.AddGameObject(go);

	return go;
}