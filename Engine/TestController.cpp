#include "pch.h"
#include "TestController.h"
#include "TypeRegistry.h"
#include "ComponentMacro.h"

COMPONENT_IMPL(TestController);

void TestController::MakeJson(nlohmann::json& json) const
{
	f32 speed = 1.23f;

	json["speed"] = speed;
}

void TestController::LoadJson(const nlohmann::json& json)
{
	_speed = json["speed"];
}

void TestController::TestFunc()
{
	int a = 0;
}
