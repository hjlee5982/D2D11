#pragma once

class Mesh;
class Material;

class BoxCollider2D : public Component
{
public:
	virtual void Awake()      override;
	virtual void Start()      override;
	virtual void Update()     override;
	virtual void LateUpdate() override;
public:
	sptr<Mesh>     GetMesh();
	sptr<Material> GetMaterial();
private:
	sptr<Mesh>     _mesh;
	sptr<Material> _material;
};

