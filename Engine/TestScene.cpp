#include "pch.h"
#include "TestScene.h"
#include<fstream>

TestGameObject* TestScene::CreateObject()
{
    auto obj = makeUptr<TestGameObject>();
    TestGameObject* raw = obj.get();

    _objects.push_back(std::move(obj));

    return raw;
}

void TestScene::Save(const string& path)
{
    nlohmann::json json;
    json["objects"] = nlohmann::json::array();

    for (const auto& obj : _objects)
    {
        json["objects"].push_back(obj->MakeJson());
    }

    std::ofstream file(path);
    file << json.dump(4);
}

void TestScene::Load(const string& path)
{
    std::ifstream file(path);

    nlohmann::json json;
    file >> json;

    for (const auto& objJson : json["objects"])
    {
        auto obj = makeUptr<TestGameObject>();
        obj->LoadJson(objJson);
        _objects.push_back(std::move(obj));
    }
}
