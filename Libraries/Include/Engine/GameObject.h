#pragma once

class GameObject : public Object
{
public:
	GameObject();
	virtual ~GameObject() = default;
public:
	template<typename T, typename ...Args>
	sptr<T> AddComponent(Args&& ... args)
	{
		static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");

		auto idx = std::type_index(typeid(T));
		
		if (components.find(idx) != components.end())
		{
			sptr<T> component = makeSptr<T>(args...);

			components.emplace(idx, component);

			return component;
		}

		return nullptr;
	}
public:
	template<typename T, typename ...Args>
	sptr<T> GetComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");

		auto it = components.find(std::type_index(typeid(T)));

		if (it != components.end())
		{
			return std::static_pointer_cast<T>(it->second);
		}
	}
public:
	sptr<class Component> GetComponent();
private:
	Dictionary<std::type_index, sptr<class Component>> components;
};

