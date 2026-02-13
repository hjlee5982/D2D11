#pragma once

class TestComponent;

class TypeRegistry
{
public:
    using CreateComponentFunc = uptr<TestComponent>(*)();
public:
    static void Register(const string& name, CreateComponentFunc func);
    static uptr<TestComponent> Create(const string& name);
private:
    static Dictionary<std::string, CreateComponentFunc>& GetDict();
};

class TypeRegistrar
{
public:
    TypeRegistrar(const std::string& name, TypeRegistry::CreateComponentFunc func)
    {
        TypeRegistry::Register(name, func);
    }
};