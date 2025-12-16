#pragma once

#include "Collider.h"

struct AABB
{
	Vector3 min;
	Vector3 max;
};

class BoxCollider2D : public Collider, public std::enable_shared_from_this<BoxCollider2D>
{
public:
	virtual void Init()  override;
public:
	virtual void Start()  override;
	virtual void Update() override;
public:
	virtual void Offset(Vector3 position) override;
public:
	void Size(Vector3 scale);
public:
	AABB GetAABB() { return _aabb; }
private:
	AABB    _aabb;
	Vector3 _min;
	Vector3 _max;
};

