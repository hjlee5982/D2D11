#include "pch.h"
#include "SpriteRenderer.h"
#include "AssetManager.h"
#include "Mesh.h"
#include "Material.h"
#include "Renderer.h"
#include "Texture.h"
#include "TMesh.h"

void SpriteRenderer::Init()
{
	_mesh     = ASSET.Get<TMesh<VertexTextureData>>(L"Mesh_Square");
	_material = ASSET.Get<Material>(L"Material_Default", true);

	RENDERER.AddGameObject(Owner());
}

sptr<TMeshBase> SpriteRenderer::GetMesh()
{
	return _mesh;
}

sptr<Material> SpriteRenderer::GetMaterial()
{
	return _material;
}

void SpriteRenderer::SetMesh(sptr<TMeshBase> mesh)
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
