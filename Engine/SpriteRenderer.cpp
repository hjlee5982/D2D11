#include "pch.h"
#include "SpriteRenderer.h"
#include "AssetManager.h"
#include "Mesh.h"
#include "Material.h"
#include "Renderer.h"

void SpriteRenderer::Awake()
{
	_mesh     = AssetManager::Instance().Get<Mesh>(L"Mesh_Square");
	_material = AssetManager::Instance().Get<Material>(L"Material_Default");

	Renderer::Instance().AddGameObjectToRenderer(Owner());
}

void SpriteRenderer::Start()
{
}

void SpriteRenderer::Update()
{
}

void SpriteRenderer::LateUpdate()
{
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
