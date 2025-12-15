#include "pch.h"
#include "UIBoundary.h"
#include "AssetManager.h"
#include "Mesh.h"
#include "Material.h"
#include "RenderManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "TMesh.h"

void UIBoundary::Init()
{
	_mesh     = ASSET.Get<TMesh<VertexColliderData>>(L"Mesh_BoxCollider2D");
	_material = ASSET.Get<Material>(L"Material_Collider");
	

	_boundaryTransform = makeSptr<Transform>();
	_boundaryTransform->SetParent(Owner()->transform, _boundaryTransform);

	RENDERER.AddUIBoundary(shared_from_this());
}