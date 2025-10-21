#include "pch.h"
#include "AssetManager.h"
#include "Mesh.h"

void AssetManager::Awake()
{
	CreateDefaultResource();
}

void AssetManager::CreateDefaultResource()
{
	// 기본 메시 로드
	{
		sptr<Mesh> mesh = makeSptr<Mesh>();
		mesh->CreateSquare();
	}
	// 기본 쉐이더 로드
	{

	}
	// 기본 머티리얼 로드
	{

	}
}
