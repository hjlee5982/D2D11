#include "pch.h"
#include "BoxCollider2D.h"
#include "AssetManager.h"
#include "RenderManager.h"
#include "Mesh.h"
#include "Material.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "TMesh.h"
#include "VertexData.h"

void BoxCollider2D::Init()
{
	_mesh     = ASSET.Get<TMesh<VertexColliderData>>(L"Mesh_BoxCollider2D");
	_material = ASSET.Get<Material>(L"Material_Collider");

	RENDERER.AddCollider(shared_from_this());
	COLLISION.AddCollider(shared_from_this());
}

void BoxCollider2D::Start()
{
	Vector3 localScale    = _localTransform->GetLocalScale();
	Vector3 localPosition = _localTransform->GetLocalPosition();

	_min.x = localPosition.x - localScale.x / 2;
	_min.y = localPosition.y - localScale.y / 2;
	_max.x = localPosition.x + localScale.x / 2;
	_max.y = localPosition.y + localScale.y / 2;
}

void BoxCollider2D::Update()
{
	// AABB °»½Å
	_aabb.min = XMVector3TransformCoord(_min, Owner()->transform->GetWorldMatrix());
	_aabb.max = XMVector3TransformCoord(_max, Owner()->transform->GetWorldMatrix());

	_worldTransform->_worldMatrix = _localTransform->_worldMatrix * Owner()->transform->_worldMatrix;
}

void BoxCollider2D::Size(Vector3 scale)
{
	_localTransform->SetLocalScale(scale);
}
