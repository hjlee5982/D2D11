#include "pch.h"
#include "AssetManager.h"
#include "Mesh.h"

void AssetManager::Awake()
{
	CreateDefaultResource();
}

void AssetManager::CreateDefaultResource()
{
	// �⺻ �޽� �ε�
	{
		sptr<Mesh> mesh = makeSptr<Mesh>();
		mesh->CreateSquare();
	}
	// �⺻ ���̴� �ε�
	{

	}
	// �⺻ ��Ƽ���� �ε�
	{

	}
}
