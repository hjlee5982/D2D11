#include "pch.h"
#include "SpriteRenderer.h"
#include "AssetManager.h"
#include "Mesh.h"
#include "Material.h"
#include "Renderer.h"

SpriteRenderer::SpriteRenderer()
{
	_mesh     = AssetManager::Instance().Get<Mesh>    (L"Mesh_Square");
	_material = AssetManager::Instance().Get<Material>(L"Material_Default");
}

void SpriteRenderer::SetOwner(sptr<class GameObject> owner)
{
	gameObject = owner;

	Renderer::Instance().AddToRenderer(gameObject);
}

sptr<Mesh> SpriteRenderer::GetMesh()
{
	return _mesh;
}

sptr<Material> SpriteRenderer::GetMaterial()
{
	return _material;
}

void SpriteRenderer::SetMesh(sptr<Mesh> mesh)
{
	_mesh = mesh;
}

void SpriteRenderer::SetMaterial(sptr<Material> material)
{
	_material = material;
}
