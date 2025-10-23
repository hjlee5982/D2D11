#include "pch.h"
#include "AssetManager.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"

static wstring shaderPath  = L"../Assets/Shader/";
static wstring texturePath = L"../Assets/Image/";

void AssetManager::Awake()
{
	CreateDefaultResource();
}

void AssetManager::CreateDefaultResource()
{
	// 기본 메시 생성
	{
		sptr<Mesh> mesh = makeSptr<Mesh>();
		mesh->CreateMesh(EMeshType::Square);
		Add(L"Mesh_Square", mesh);
	}
	// 기본 쉐이더 생성
	{
		sptr<Shader> shader = makeSptr<Shader>();
		shader->CreateShader(shaderPath + L"Default");
		Add(L"Shader_Default", shader);
	}
	// 기본 텍스쳐 생성
	{
		sptr<Texture> texture = makeSptr<Texture>();
		texture->CreateTexture(texturePath + L"BackGround.png");
		Add(L"Texture_BackGround", texture);
	}
	// 기본 머티리얼 생성
	{
		sptr<Material> material = makeSptr<Material>();
		{
			material->SetTexture(Get<Texture>(L"Texture_BackGround"));
			material->SetShader (Get<Shader> (L"Shader_Default"));
		}
		Add(L"Material_Default", material);
	}
}
