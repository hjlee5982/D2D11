#include "pch.h"
#include "BoxCollider2D.h"
#include "AssetManager.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Material.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "Transform.h"

void BoxCollider2D::Init()
{
	_mesh     = ASSET.Get<Mesh>(L"Mesh_BoxCollider2D");
	_material = ASSET.Get<Material>(L"Material_Collider");

	_colliderTransform = makeSptr<Transform>();
	_colliderTransform->SetParent(Owner()->transform, _colliderTransform);

	RENDERER.AddCollider(shared_from_this());
	COLLISION.AddCollider(shared_from_this());
}

void BoxCollider2D::Start()
{
	Vector3 localScale    = _colliderTransform->GetLocalScale();
	Vector3 localPosition = _colliderTransform->GetLocalPosition();

	_min.x = localPosition.x - localScale.x / 2;
	_min.y = localPosition.y - localScale.y / 2;
	_max.x = localPosition.x + localScale.x / 2;
	_max.y = localPosition.y + localScale.y / 2;
}

void BoxCollider2D::Update()
{
	// AABB 갱신
	_aabb.min = XMVector3TransformCoord(_min, Owner()->transform->GetWorldMatrix());
	_aabb.max = XMVector3TransformCoord(_max, Owner()->transform->GetWorldMatrix());

	// 월드 갱신

}

void BoxCollider2D::SetLocalPosition(Vector3 position)
{
	_colliderTransform->SetLocalPosition(position);
}

void BoxCollider2D::SetLocalScale(Vector3 scale)
{
	_colliderTransform->SetLocalScale(scale);
}
