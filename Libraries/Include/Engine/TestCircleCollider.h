#pragma once

#include "TestCollider.h"
#include "TestGameObject.h"

#include "Struct.h"

class TestCircleCollider : public TestCollider
{
	COMPONENT_BODY(TestCircleCollider, TestCollider);
public:

	PROPERTY_FIELD
	{
		REGISTER_FIELD(TestCircleCollider, _circleColliderValue);
		REGISTER_FIELD(TestCircleCollider, desc);
		REGISTER_OBJECT_REF(TestCircleCollider, _target);
	}
public:
	i32 _circleColliderValue = 0;
	TestGameObject* _target = nullptr;
	TestDesc desc;
};

