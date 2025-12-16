#pragma once

#include "Collider.h"

class CircleCollider2D : public Collider, public std::enable_shared_from_this<CircleCollider2D>
{
public:
	virtual void Init() override;
public:
	virtual void Start() override;
	virtual void Update() override;
public:
	void Radius(f32 radius);
};

