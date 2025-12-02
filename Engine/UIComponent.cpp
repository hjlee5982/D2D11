#include "pch.h"
#include "UIComponent.h"
#include "AssetManager.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"

sptr<Mesh> UIComponent::GetMesh()
{
    return _mesh;
}

sptr<Material> UIComponent::GetMaterial()
{
    return _material;
}

void UIComponent::SetMesh(sptr<Mesh> mesh)
{
    _mesh = mesh;
}

void UIComponent::SetTexture(sptr<Texture> texture)
{
    _material->SetTexture(texture);
}

void UIComponent::SetMaterial(sptr<Material> material)
{
    _material = material;
}
