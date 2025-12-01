#pragma once

#include "Component.h"

class Checker : public Component
{
public:
	virtual void Update() override;
public:
	void SetGenerator(sptr<class ObjectGenerator> generator)
	{
		_generator = generator;
	}
private:
	f32 _speed = 3.f;
private:
	wptr<class ObjectGenerator> _generator;
public:
	bool _isColliding = false;
};

