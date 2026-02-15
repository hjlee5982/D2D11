#include "pch.h"
#include "TestGameObject.h"
#include "TestComponent.h"
#include "TypeRegistry.h"

nlohmann::json TestGameObject::MakeJson() const
{
    nlohmann::json json;

    json["components"] = nlohmann::json::array();

    for (const auto& comp : _components)
    {
        nlohmann::json compJson;
        compJson["type"] = comp->GetTypeName();

        comp->MakeJson(compJson["data"]);

        json["components"].push_back(compJson);
    }

    return json;
}

void TestGameObject::LoadJson(const nlohmann::json& json)
{
    for (const auto& compJson : json["components"])
    {
        string type = compJson["type"];

        TestComponent* comp = AddComponent(type);

        if (comp == nullptr)
        {
            continue;
        }

        if (compJson.contains("data"))
        {
            comp->LoadJson(compJson["data"]);
        }
    }
}

TestComponent* TestGameObject::AddComponent(const string& typeName)
{
    auto comp = TypeRegistry::Create(typeName);

    if (comp == nullptr)
    {
        return nullptr;
    }

    TestComponent* raw = comp.get();

    _components.push_back(std::move(comp));

    return raw;
}

TestComponent* TestGameObject::AddComponent1(const string& typeName)
{
    auto comp = TypeRegistry::Create1(typeName);

    if (comp == nullptr)
    {
        return nullptr;
    }

    TestComponent* raw = comp.get();

    _components.push_back(std::move(comp));

    return raw;
}
