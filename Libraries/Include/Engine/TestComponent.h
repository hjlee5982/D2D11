#pragma once

class TestComponent
{
public:
	virtual ~TestComponent() = default;
public:
	virtual const char* GetTypeName() const = 0;
};

