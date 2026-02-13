#pragma once

#include "TestComponent.h"
#include "ComponentMacro.h"

class TestCamera : public TestComponent
{
	COMPONENT_BODY(TestCamera);
public:
	virtual void MakeJson(nlohmann::json& json) const override;
	virtual void LoadJson(const nlohmann::json& json) override;
private:
	f32 _pov = 0.f;
public:
	void TestFunc();
};

