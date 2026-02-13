#pragma once

#include "TestComponent.h"
#include "ComponentMacro.h"

class TestTransform : public TestComponent
{
	COMPONENT_BODY(TestTransform);
public:
	virtual void MakeJson(nlohmann::json& json) const override;
	virtual void LoadJson(const nlohmann::json& json) override;
private:
	Vector3 _pos = Vector3::Zero;
	f32 _scale = 0.f;
public:
	void TestFunc();
};

