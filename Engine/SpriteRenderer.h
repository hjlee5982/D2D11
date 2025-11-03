#pragma once

class Mesh;
class Material;

class SpriteRenderer : public Component
{
public:
	virtual ~SpriteRenderer() = default;
public:
	virtual void Awake() override;
public:
	sptr<Mesh>     GetMesh();
	sptr<Material> GetMaterial();
public:
	void SetMesh(sptr<Mesh> mesh);
	void SetMaterial(sptr<Material> material);
private:
	sptr<Mesh>     _mesh;
	sptr<Material> _material;
public:
	int OrderInLayer = 0;
};

