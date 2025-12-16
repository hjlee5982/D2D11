#pragma once

#include "Component.h"

class TMeshBase;
class Material;
class Transform;

class Collider : public Component
{
public:
	virtual void Offset(Vector3 position) {}
public:
	sptr<TMeshBase> GetMesh()              { return _mesh; }
	sptr<Material>  GetMaterial()          { return _material; }
	sptr<Transform> GetColliderTransform() { return _colliderTransform; }
protected:
	sptr<TMeshBase> _mesh;
	sptr<Material>  _material;
protected:
	sptr<Transform> _colliderTransform;
	sptr<Transform> _localTransform;
};

