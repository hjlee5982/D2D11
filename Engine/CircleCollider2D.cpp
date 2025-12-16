#include "pch.h"
#include "CircleCollider2D.h"
#include "AssetManager.h"
#include "Transform.h"
#include "TMesh.h"
#include "Material.h"
#include "RenderManager.h"

void CircleCollider2D::Init()
{
	_mesh     = ASSET.Get<TMesh<VertexColliderData>>(L"Mesh_CircleCollider2D");
	_material = ASSET.Get<Material>(L"Material_Collider");

	RENDERER.AddCollider(shared_from_this());
}

void CircleCollider2D::Start()
{
}

void CircleCollider2D::Update()
{
	_worldTransform->_worldMatrix = _localTransform->_worldMatrix * Owner()->transform->_worldMatrix;
}

void CircleCollider2D::Radius(f32 radius)
{
	_localTransform->SetLocalScale(Vector3(radius * 2, radius * 2, radius * 2));
}
