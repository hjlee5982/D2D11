#pragma once

#include "Component.h"

class Mesh;
class Material;
class Transform;

class UIBoundary : public Component, public std::enable_shared_from_this<UIBoundary>
{
public:
	virtual void Init() override;
public:
	sptr<Mesh>      GetMesh()              { return _mesh;              }
	sptr<Material>  GetMaterial()          { return _material;          }
	sptr<Transform> GetBoundaryTransform() { return _boundaryTransform; }
public:
	sptr<Mesh>      _mesh;
	sptr<Material>  _material;
	sptr<Transform> _boundaryTransform;
};

