#pragma once

#include "TestComponent.h"
#include "ComponentMacro.h"

class TestTransform : public TestComponent
{
	COMPONENT_BODY(TestTransform);
public:
	void TestFunc();
};

