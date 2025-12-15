#include "pch.h"
#include "UIImage.h"
#include "AssetManager.h"
#include "Mesh.h"
#include "Material.h"
#include "TMesh.h"
#include "RenderManager.h"

void UIImage::Init()
{
	_mesh     = ASSET.Get<TMesh<VertexUIData>>(L"Mesh_UI_Square");
	_material = ASSET.Get<Material>(L"Material_UI_Image", true);

	RENDERER.AddUI(shared_from_this());
}
