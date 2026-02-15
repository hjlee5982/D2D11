#pragma once

class TestComponent;

class Field
{
public:
    string name;

    std::function<void(void*, nlohmann::json&)> serialize;
    std::function<void(void*, const nlohmann::json&)> deserialize;
};

class TypeInfo
{
public:
    string typeName;
    List<uptr<Field>> fields;
};

struct TypeData
{
    std::function<uptr<TestComponent>()> creator;
    uptr<TypeInfo> typeInfo;
};

class TypeRegistry
{
public:
    using CreateComponentFunc = uptr<TestComponent>(*)();
public:
    static void Register(const string& name, CreateComponentFunc func);
    static uptr<TestComponent> Create(const string& name);
    static uptr<TestComponent> Create1(const string& name);

    static TypeInfo* RegisterType(const string& name, std::function<uptr<TestComponent>()> creator);

private:
    static Dictionary<std::string, CreateComponentFunc>& GetDict();

    static Dictionary<string, TypeData>& GetMap();

public:
    static TypeInfo* GetTypeInfo(const string& name);
};

class TypeRegistrar
{
public:
    TypeRegistrar(const std::string& name, TypeRegistry::CreateComponentFunc func)
    {
        TypeRegistry::Register(name, func);
    }
};

template<typename Class, typename T>
void RegisterField(TypeInfo* typeInfo, const string& name, T Class::* member)
{
    auto field = makeUptr<Field>();
    field->name = name;

    field->serialize = [member, name](void* obj, nlohmann::json& json)
        {
            Class* c = static_cast<Class*>(obj);
            json[name] = c->*member;
        };

    field->deserialize = [member, name](void* obj, const nlohmann::json& json)
        {
            if (json.contains(name) == false)
            {
                return;
            }

            Class* c = static_cast<Class*>(obj);
            c->*member = json[name].get<T>();
        };

    typeInfo->fields.push_back(std::move(field));
}