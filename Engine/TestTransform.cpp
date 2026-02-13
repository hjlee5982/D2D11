#include "pch.h"
#include "TestTransform.h"
#include "TypeRegistry.h"
#include "ComponentMacro.h"
#include "JsonConverter.h"

COMPONENT_IMPL(TestTransform);

void TestTransform::MakeJson(nlohmann::json& json) const
{
	Vector3 pos = { 1.f, -5.f, 3.2f };
	f32 scale = 2.73f;

	json["position"] = pos;
	json["scale"]    = scale;
}

void TestTransform::LoadJson(const nlohmann::json& json)
{
	_pos = json["position"].get<Vector3>();
	_scale = json["scale"];
}

void TestTransform::TestFunc()
{
	int a = 0;
}
