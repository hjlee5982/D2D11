#include "pch.h"
#include "BoxCollider2D.h"
#include "AssetManager.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Material.h"
#include "CollisionManager.h"

void BoxCollider2D::Awake()
{
	_mesh     = AssetManager::Instance().Get<Mesh>(L"Mesh_BoxCollider2D");
	_material = AssetManager::Instance().Get<Material>(L"Material_Collider");

	Renderer::Instance().AddColliderToRenderer(shared_from_this());
	CollisionManager::Instance().AddCollider(shared_from_this());
}

void BoxCollider2D::Start()
{
}

void BoxCollider2D::Update()
{
}

void BoxCollider2D::LateUpdate()
{
}

sptr<Mesh> BoxCollider2D::GetMesh()
{
	return _mesh;
}

sptr<Material> BoxCollider2D::GetMaterial()
{
	return _material;
}
