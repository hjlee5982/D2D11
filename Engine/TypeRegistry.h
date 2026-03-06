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
    string parentName;

    TypeInfo* parent = nullptr;

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

    static TypeInfo* RegisterType(const string& name, std::function<uptr<TestComponent>()> creator, const string& parentName);

private:
    static Dictionary<std::string, CreateComponentFunc>& GetDict();

    static Dictionary<string, TypeData>& GetMap();

public:
    static TypeInfo* GetTypeInfo(const string& name);

    static void SerializeType(void* obj, TypeInfo* type, nlohmann::json& json)
    {
        if (type->parent != nullptr)
        {
            SerializeType(obj, type->parent, json);
        }

        for (auto& field : type->fields)
        {
            field->serialize(obj, json);
        }
    }

    static void DeserializeType(void* obj, TypeInfo* type, const nlohmann::json& json)
    {
        if (type->parent != nullptr)
        {
            DeserializeType(obj, type->parent, json);
        }

        for (auto& field : type->fields)
        {
            field->deserialize(obj, json);
        }
    }

    static void ResolveParents()
    {
        auto& map = GetMap();

        for (auto& [name, data] : map)
        {
            auto& type = data.typeInfo;

            if (type->parentName.empty())
            {
                continue;
            }

            auto it = map.find(type->parentName);

            if (it != map.end()) 
            {
                type->parent = it->second.typeInfo.get();
            }
        }
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