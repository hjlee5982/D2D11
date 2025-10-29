#pragma once

class Mesh;
class Material;

class BoxCollider2D : public Component, public std::enable_shared_from_this<BoxCollider2D>
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

