#pragma once

class GameObject : public Object, public std::enable_shared_from_this<GameObject>
{
public:
	virtual ~GameObject() = default;
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

			_components.emplace(idx, component);

			return component;
		}

		return nullptr;
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

	return go;
}