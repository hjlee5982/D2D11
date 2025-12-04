#pragma once

#include "Component.h"
#include "VertexData.h"
#include "TMesh.h"

class Texture;
class Material;

class UIComponent : public Component
{
public:
	sptr<TMesh<VertexUIData>> GetMesh();
	sptr<Material>            GetMaterial();
public:
	void SetMesh(sptr<TMesh<VertexUIData>> mesh);
	void SetTexture(sptr<Texture>   texture);
	void SetMaterial(sptr<Material> material);
public:
	Vector4 color = { 1.f, 1.f, 1.f, 1.f };
protected:
	sptr<TMesh<VertexUIData>> _mesh;
	sptr<Material>            _material;
};

