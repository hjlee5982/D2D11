#pragma once

class Mesh;
class Material;

class SpriteRenderer : public Component
{
public:
	virtual ~SpriteRenderer() = default;
public:
	virtual void Awake()      override;
	virtual void Start()	  override;
	virtual void Update()     override;
	virtual void LateUpdate() override;
public:
	sptr<Mesh>     GetMesh();
	sptr<Material> GetMaterial();
public:
	bool IsWireFrame()
	{
		return _wireFrame;
	}
public:
	void SetMesh(sptr<Mesh> mesh);
	void SetMaterial(sptr<Material> material);
public:
	void WireFrame(bool is)
	{
		_wireFrame = is;
	}
private:
	sptr<Mesh>     _mesh;
	sptr<Material> _material;
private:
	bool _wireFrame = false;
};

