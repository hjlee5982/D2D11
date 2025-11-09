#pragma once

class Mesh;
class Texture;
class Material;

class SpriteRenderer : public Component
{
public:
	virtual void MakeJson() override;
	virtual void LoadJson() override;
public:
	virtual void Init() override;
public:
	sptr<Mesh>     GetMesh();
	sptr<Material> GetMaterial();
public:
	void SetMesh(sptr<Mesh> mesh);
	void SetTexture(sptr<Texture> texture);
	void SetMaterial(sptr<Material> material);
private:
	sptr<Mesh>     _mesh;
	sptr<Material> _material;
public:
	int OrderInLayer = 0;
};

