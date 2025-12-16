#include "pch.h"
#include "CircleCollider2D.h"
#include "AssetManager.h"
#include "Transform.h"
#include "TMesh.h"
#include "Material.h"

void CircleCollider2D::Init()
{
	_mesh     = ASSET.Get<TMesh<VertexColliderData>>(L"Mesh_CircleCollider2D");
	_material = ASSET.Get<Material>(L"Material_Collider");

	_colliderTransform = makeSptr<Transform>();
	_colliderTransform->SetParent(Owner()->transform);
}

void CircleCollider2D::Start()
{
}

void CircleCollider2D::Update()
{
}

void CircleCollider2D::Offset(Vector3 position)
{
}

void CircleCollider2D::Radius(f32 radius)
{
	_radius = radius;
}
