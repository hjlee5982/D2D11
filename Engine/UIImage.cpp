#include "pch.h"
#include "UIImage.h"
#include "AssetManager.h"
#include "Mesh.h"
#include "Material.h"

void UIImage::Init()
{
	_mesh     = ASSET.Get<Mesh>(L"Mesh_Square");
	_material = ASSET.Get<Material>(L"Material_Image", true);
}
