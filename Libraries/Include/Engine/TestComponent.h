#pragma once

class TestComponent
{
public:
	virtual ~TestComponent() = default;
public:
	virtual const char* GetTypeName() const = 0;
public:
	virtual void MakeJson(nlohmann::json& json) const;
	virtual void LoadJson(const nlohmann::json& json);
};

