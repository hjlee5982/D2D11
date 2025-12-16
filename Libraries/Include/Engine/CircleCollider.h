#pragma once

#include "Collider.h"

class CircleCollider : public Collider
{
public:
	virtual void Init() override;
public:
	virtual void Start() override;
	virtual void Update() override;
public:
	virtual void SetLocalPosition(Vector3 position) override;
	virtual void SetLocalScale(f32 scale) override;
};

