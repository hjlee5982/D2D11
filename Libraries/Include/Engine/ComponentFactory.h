#pragma once

#include "Component.h"

class ComponentFactory : public Singleton<ComponentFactory>
{
	using CreateFucn = std::function<sptr<Component>()>;
public:
	static Dictionary<string, CreateFucn>& Registry()
	{
		static Dictionary<string, CreateFucn> registry;
		return registry;
	}
	static void Register(const string& name, CreateFucn func)
	{
		Registry()[name] = func;
	}
	static sptr<Component> Create(const string& name)
	{
		auto& reg = Registry();

		if (auto it = reg.find(name); it != reg.end())
		{
			return it->second();
		}

		return nullptr;
	}
public:
	virtual void Awake() override;
};

#define REFLECTION_COMPONENT(T)											 \
public:																	 \
	virtual const char* GetTypeName() const override { return #T;}		 \
private:																 \
struct T##_RegisterHelper												 \
{																		 \
	T##_RegisterHelper()												 \
	{																	 \
		ComponentFactory::Register(#T, []() {return makeSptr<T>();});	 \
	}																	 \
};																		 \
inline static T##_RegisterHelper T##_regHelper;