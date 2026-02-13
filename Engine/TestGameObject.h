#pragma once

#include "TestComponent.h"

class TestGameObject
{
public:
	nlohmann::json MakeJson() const;
	void LoadJson(const nlohmann::json& json);
public:
	TestComponent* AddComponent(const string& typeName);
private:
	List<uptr<TestComponent>> _components;
};

