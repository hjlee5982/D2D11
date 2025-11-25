#pragma once

#include "Component.h"

class UIBoundary : public Component, public std::enable_shared_from_this<UIBoundary>
{
public:
	sptr<class Mesh>      _mesh;
	sptr<class Material>  _material;
	sptr<class Transform> _boundaryTransform;
};

