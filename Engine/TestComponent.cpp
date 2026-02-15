#include "pch.h"
#include "TestComponent.h"
#include "TypeRegistry.h"

void TestComponent::MakeJson(nlohmann::json& json) const
{
	json["type"] = GetTypeName();

	TypeInfo* info = TypeRegistry::GetTypeInfo(GetTypeName());

	for (auto& field : info->fields)
	{
		field->serialize((void*)this, json);
	}
}

void TestComponent::LoadJson(const nlohmann::json& json)
{
	TypeInfo* info = TypeRegistry::GetTypeInfo(GetTypeName());

	for (auto& field : info->fields)
	{
		field->deserialize(this, json);
	}
}
