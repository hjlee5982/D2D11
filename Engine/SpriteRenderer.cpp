#include "pch.h"
#include "SpriteRenderer.h"
#include "AssetManager.h"
#include "Mesh.h"
#include "Material.h"
#include "Renderer.h"
#include "Texture.h"

void SpriteRenderer::MakeJson()
{
}

void SpriteRenderer::LoadJson(const nlohmann::json& json)
{
}

void SpriteRenderer::Init()
{
	_mesh     = ASSET.Get<Mesh>(L"Mesh_Square");
	_material = ASSET.Get<Material>(L"Material_Default", true);

	RENDERER.AddGameObject(Owner());
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

void SpriteRenderer::SetTexture(sptr<Texture> texture)
{
	_material->SetTexture(texture);
}

void SpriteRenderer::SetMaterial(sptr<Material> material)
{
	_material = material;
}
