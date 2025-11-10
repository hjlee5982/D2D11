#pragma once

#include "Object.h"

class ObjectFactory : public Singleton<ObjectFactory>
{
	using CreateFucn = std::function<sptr<Object>()>;
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
	static sptr<Object> Create(const string& name)
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

#define REFLECTION(T)															        \
public:																					\
	virtual const uint64_t GetType() const override { return typeid(T).hash_code(); }	\
	virtual const char* GetTypeName() const override { return #T;}						\
private:																				\
struct T##_RegisterHelper																\
{																						\
	T##_RegisterHelper()																\
	{																					\
		ObjectFactory::Register(#T, []() {return makeSptr<T>();});					    \
	}																					\
};																						\
inline static T##_RegisterHelper T##_regHelper;
