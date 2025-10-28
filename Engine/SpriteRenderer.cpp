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

	Renderer::Instance().AddToRenderer(gameObject);
}

void SpriteRenderer::Start()
{
	int a = 0;
}

void SpriteRenderer::Update()
{
	int a = 0;
}

void SpriteRenderer::LateUpdate()
{
	int a = 0;
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
