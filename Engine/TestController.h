#pragma once

#include "TestComponent.h"
#include "ComponentMacro.h"

class TestController : public TestComponent
{
	COMPONENT_BODY(TestController);
public:
	virtual void MakeJson(nlohmann::json& json) const override;
	virtual void LoadJson(const nlohmann::json& json) override;
private:
	f32 _speed = 0.f;
public:
	void TestFunc();
};

