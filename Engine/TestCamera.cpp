#include "pch.h"
#include "TestCamera.h"
#include "TypeRegistry.h"
#include "ComponentMacro.h"

COMPONENT_IMPL(TestCamera);

void TestCamera::MakeJson(nlohmann::json& json) const
{
	f32 pov = 60.f;

	json["pov"] = pov;
}

void TestCamera::LoadJson(const nlohmann::json& json)
{
	_pov = json["pov"];
}

void TestCamera::TestFunc()
{
	int a = 0;
}
