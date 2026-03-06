#pragma once

#include "TestCollider.h"

class TestBoxCollider : public TestCollider
{
	COMPONENT_BODY(TestBoxCollider, TestCollider);
public:
	PROPERTY_FIELD
	{
		REGISTER_FIELD(TestBoxCollider, _boxColliderValue);
	}
public:
	i32 _boxColliderValue = 0;
};