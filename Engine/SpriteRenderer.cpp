#include "pch.h"
#include "SpriteRenderer.h"
#include "AssetManager.h"
#include "Mesh.h"
#include "Material.h"
#include "RenderManager.h"
#include "Texture.h"
#include "TMesh.h"
#include "Transform.h"

void SpriteRenderer::Init()
{
	_mesh     = ASSET.Get<TMesh<VertexTextureData>>(L"Mesh_Square");
	_material = ASSET.Get<Material>(L"Material_Default", true);

	RENDERER.AddRenderer(shared_from_this());
}

void SpriteRenderer::CollectRenderData(RenderContext& ctx)
{
	SpriteRendererCommand cmd;
	{
		cmd.WorldMatrix  = Owner()->transform->GetWorldMatrix();
		cmd.Mesh         = _mesh;
		cmd.Material     = _material;
		cmd.OrderInLayer = OrderInLayer;
	}
	ctx.spriteCmds.push_back(cmd);
}