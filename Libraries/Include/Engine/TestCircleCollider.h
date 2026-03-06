#pragma once

#include "TestCollider.h"

class TestCircleCollider : public TestCollider
{
	COMPONENT_BODY(TestCircleCollider, TestCollider);
public:
	PROPERTY_FIELD
	{
		REGISTER_FIELD(TestCircleCollider, _circleColliderValue);
	}
public:
	i32 _circleColliderValue = 0;
};

