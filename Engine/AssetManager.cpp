#include "pch.h"
#include "AssetManager.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "VertexData.h"
#include "TMesh.h"

static wstring shaderPath      = L"../Assets/Shader/";
static wstring texturePath     = L"../Assets/Image/";
static wstring engineAssetPath = L"../Engine/EngineAssets/";

void AssetManager::Awake()
{
	CreateShader();
	CreateMesh();
	CreateTexture();
	CreateMaterial();
}

void AssetManager::CreateShader()
{
	// 기본 쉐이더
	{
		sptr<Shader> shader = makeSptr<Shader>();
		shader->CreateShader(shaderPath + L"Default");
		Add(L"Shader_Default", shader);
	}
	// 콜라이더 쉐이더
	{
		sptr<Shader> shader = makeSptr<Shader>();
		shader->CreateShader(shaderPath + L"Collider");
		Add(L"Shader_Collider", shader);
	}
	// UI 폰트 쉐이더
	{
		sptr<Shader> shader = makeSptr<Shader>();
		shader->CreateShader(shaderPath + L"Font");
		Add(L"Shader_UI_Font", shader);
	}
	// UI 이미지 쉐이더
	{
		sptr<Shader> shader = makeSptr<Shader>();
		shader->CreateShader(shaderPath + L"Image");
		Add(L"Shader_UI_Image", shader);
	}
}

void AssetManager::CreateMesh()
{
	// BoxCollider2D
	{
		sptr<TMesh<VertexColliderData>> mesh = makeSptr<TMesh<VertexColliderData>>();
		mesh->CreateMesh(ETMeshType::Square);
		Add(L"Mesh_BoxCollider2D", mesh);
	}
	// CircleCollider2D
	{
		sptr<TMesh<VertexColliderData>> mesh = makeSptr<TMesh<VertexColliderData>>();
		mesh->CreateMesh(ETMeshType::Circle);
		Add(L"Mesh_CircleCollider2D", mesh);
	}
	// Square
	{
		sptr<TMesh<VertexTextureData>> mesh = makeSptr<TMesh<VertexTextureData>>();
		mesh->CreateMesh(ETMeshType::Square);
		Add(L"Mesh_Square", mesh);
	}
	// Square_UI
	{
		sptr<TMesh<VertexUIData>> mesh = makeSptr<TMesh<VertexUIData>>();
		mesh->CreateMesh(ETMeshType::Square);
		Add(L"Mesh_UI_Square", mesh);
	}
}

void AssetManager::CreateTexture()
{
	// 스프라이트 렌더러 디폴트 텍스쳐
	{
		sptr<Texture> texture = makeSptr<Texture>();
		texture->CreateTexture(engineAssetPath + L"Image/DefaultTexture.png");
		Add(L"Texture_Default", texture);
	}
	// 폰트 아틀라스
	{
		sptr<Texture> texture = makeSptr<Texture>();
		texture->CreateTexture(L"../Data/Font/EngineFont.png");
		Add(L"Texture_UI_Font", texture);
	}
	// UI 이미지 기본 텍스쳐
	{
		sptr<Texture> texture = makeSptr<Texture>();
		texture->CreateTexture(engineAssetPath + L"Image/Square.png");
		Add(L"Texture_UI_Default", texture);
	}
}

void AssetManager::CreateMaterial()
{
	// 스프라이트 렌더러 기본 머티리얼
	{
		sptr<Material> material = makeSptr<Material>();
		{
			material->SetTexture(Get<Texture>(L"Texture_Default"));
			material->SetShader(Get<Shader>(L"Shader_Default"));
		}
		Add(L"Material_Default", material);
	}
	// 콜라이더 머티리얼
	{
		sptr<Material> material = makeSptr<Material>();
		{
			// 콜라이더는 텍스쳐 안씀
			material->SetShader(Get<Shader>(L"Shader_Collider"));
		}
		Add(L"Material_Collider", material);
	}
	// UI 폰트 머티리얼
	{
		sptr<Material> material = makeSptr<Material>();
		{
			material->SetTexture(Get<Texture>(L"Texture_UI_Font"));
			material->SetShader(Get<Shader>(L"Shader_UI_Font"));
		}
		Add(L"Material_UI_Font", material);
	}
	// UI 이미지 머티리얼
	{
		sptr<Material> material = makeSptr<Material>();
		{
			material->SetTexture(Get<Texture>(L"Texture_UI_Default"));
			material->SetShader(Get<Shader>(L"Shader_UI_Image"));
		}
		Add(L"Material_UI_Image", material);
	}
}
