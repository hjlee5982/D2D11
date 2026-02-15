#pragma once

#include "TestComponent.h"
#include "ComponentMacro.h"

class TestController : public TestComponent
{
public:
	COMPONENT_BODY(TestController);
public:
	PROPERTY_FIELD
	{
		REGISTER_FIELD(TestController, _speed);
		REGISTER_FIELD(TestController, _position);
	}
public:
	f32 _speed = 3.f;
	Vector3 _position = { 0.f, 2.f, 0.f };
};

