#pragma once

#include "Component.h"

class Mesh;
class Texture;
class Material;
class TMeshBase;

class SpriteRenderer : public Component
{
public:
	virtual void Init() override;
public:
	sptr<TMeshBase>     GetMesh();
	sptr<Material> GetMaterial();
public:
	void SetMesh(sptr<TMeshBase> mesh);
	void SetTexture(sptr<Texture> texture);
	void SetMaterial(sptr<Material> material);
private:
	sptr<TMeshBase> _mesh;
	sptr<Material> _material;
public:
	int OrderInLayer = 0;
};