#pragma once

#include "Component.h"

class Mesh;
class Texture;
class Material;

class UIComponent : public Component
{
public:
	sptr<Mesh>     GetMesh();
	sptr<Material> GetMaterial();
public:
	void SetMesh   (sptr<Mesh> mesh);
	void SetTexture(sptr<Texture> texture);
	void SetMaterial(sptr<Material> material);
protected:
	sptr<Mesh>     _mesh;
	sptr<Material> _material;
};

