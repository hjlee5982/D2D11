#include "pch.h"
#include "TypeRegistry.h"
#include "TestComponent.h"

std::unordered_map<std::string, TypeRegistry::CreateComponentFunc>&
TypeRegistry::GetDict()
{
    static std::unordered_map<std::string, CreateComponentFunc> dict;

    return dict;
}

void TypeRegistry::Register(const std::string& name, CreateComponentFunc func)
{
    GetDict()[name] = func;
}

uptr<TestComponent> TypeRegistry::Create(const std::string& name)
{
    auto& dict = GetDict();

    auto it = dict.find(name);

    if (it == dict.end())
    {
        return nullptr;
    }

    return it->second();
}