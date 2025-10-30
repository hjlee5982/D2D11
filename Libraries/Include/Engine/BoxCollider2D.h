#pragma once

class Mesh;
class Material;

struct AABB
{
	Vector3 min;
	Vector3 max;
};

class BoxCollider2D : public Component, public std::enable_shared_from_this<BoxCollider2D>
{
public:
	virtual void Awake()  override;
	virtual void Start()  override;
	virtual void Update() override;
public:
	virtual void OnCollisionEnter(sptr<BoxCollider2D> collider) override;
public:
	sptr<Mesh>      GetMesh()              { return _mesh;              }
	sptr<Material>  GetMaterial()          { return _material;          }
	sptr<Transform> GetColliderTransform() { return _colliderTransform; }
public:
	AABB GetAABB() { return _aabb; }
private:
	sptr<Mesh>      _mesh;
	sptr<Material>  _material;
	sptr<Transform> _colliderTransform;
private:
	AABB    _aabb;
	Vector3 _min;
	Vector3 _max;
};

