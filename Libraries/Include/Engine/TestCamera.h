#pragma once

#include "TestComponent.h"
#include "ComponentMacro.h"

class TestCamera : public TestComponent
{
	COMPONENT_BODY(TestCamera);
private:
	f32 _pov = 0.f;
public:
	static void RegisterFields(TypeInfo* type)
	{
		REGISTER_FIELD(TestCamera, _pov);
	}
};

