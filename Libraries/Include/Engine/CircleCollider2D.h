#pragma once

#include "Collider.h"

class CircleCollider2D : public Collider
{
public:
	virtual void Init() override;
public:
	virtual void Start() override;
	virtual void Update() override;
public:
	virtual void Offset(Vector3 position) override;
public:
	void Radius(f32 radius);
private:
	f32 _radius = 0.5f;
};

