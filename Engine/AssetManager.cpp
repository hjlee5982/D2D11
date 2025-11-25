#include "pch.h"
#include "AssetManager.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"

static wstring shaderPath  = L"../Assets/Shader/";
static wstring texturePath = L"../Assets/Image/";
static wstring engineAssetPath = L"../Engine/EngineAssets/";

void AssetManager::Awake()
{
	CreateDefaultResource();
}

void AssetManager::CreateDefaultResource()
{
	// 기본 메시 생성
	{
		// Square
		{
			sptr<Mesh> mesh = makeSptr<Mesh>();
			mesh->CreateMesh(EMeshType::Square);
			Add(L"Mesh_Square", mesh);
		}
		// SquareCollider
		{
			sptr<Mesh> mesh = makeSptr<Mesh>();
			mesh->CreateMesh(EMeshType::BoxCollider2D);
			Add(L"Mesh_BoxCollider2D", mesh);
		}
	}
	// 기본 쉐이더 생성
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
		// 폰트 쉐이더
		{
			sptr<Shader> shader = makeSptr<Shader>();
			shader->CreateShader(shaderPath + L"Font");
			Add(L"Shader_Font", shader);
		}
		
	}
	// 기본 텍스쳐 생성
	{
		{
			sptr<Texture> texture = makeSptr<Texture>();
			texture->CreateTexture(engineAssetPath + L"Image/DefaultTexture.png");
			Add(L"Texture_Default", texture);
		}
		// 폰트 아틀라스 로드
		{
			sptr<Texture> texture = makeSptr<Texture>();
			texture->CreateTexture(L"../Data/Font/EngineFont.png");
			ASSET.Add(L"Texture_Font", texture);
		}
	}
	// 기본 머티리얼 생성
	{
		// 기본 머티리얼
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
		// 폰트 머티리얼
		{
			sptr<Material> material = makeSptr<Material>();
			{
				material->SetTexture(Get<Texture>(L"Texture_Font"));
				material->SetShader(Get<Shader>(L"Shader_Font"));
			}
			Add(L"Material_Font", material);
		}
	}
}
