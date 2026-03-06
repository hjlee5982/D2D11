#pragma once

#include "ComponentMacro.h"

class TestComponent
{
	ROOT_COMPONENT_BODY(TestComponent)
public:
	PROPERTY_FIELD{}
public:
	virtual ~TestComponent() = default;
public:
	virtual void MakeJson(nlohmann::json& json) const;
	virtual void LoadJson(const nlohmann::json& json);
};

