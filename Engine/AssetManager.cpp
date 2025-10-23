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
	// �⺻ �޽� ����
	{
		sptr<Mesh> mesh = makeSptr<Mesh>();
		mesh->CreateMesh(EMeshType::Square);
		Add(L"Mesh_Square", mesh);
	}
	// �⺻ ���̴� ����
	{
		sptr<Shader> shader = makeSptr<Shader>();
		shader->CreateShader(shaderPath + L"Default");
		Add(L"Shader_Default", shader);
	}
	// �⺻ �ؽ��� ����
	{
		sptr<Texture> texture = makeSptr<Texture>();
		texture->CreateTexture(texturePath + L"BackGround.png");
		Add(L"Texture_BackGround", texture);
	}
	// �⺻ ��Ƽ���� ����
	{
		sptr<Material> material = makeSptr<Material>();
		{
			material->SetTexture(Get<Texture>(L"Texture_BackGround"));
			material->SetShader (Get<Shader> (L"Shader_Default"));
		}
		Add(L"Material_Default", material);
	}
}
