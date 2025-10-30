#include "pch.h"
#include "SpriteRenderer.h"
#include "AssetManager.h"
#include "Mesh.h"
#include "Material.h"
#include "Renderer.h"

void SpriteRenderer::Awake()
{
	_mesh     = ASSET.Get<Mesh>(L"Mesh_Square");
	_material = ASSET.Get<Material>(L"Material_Default");

	RENDERER.AddGameObjectToRenderer(Owner());
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
