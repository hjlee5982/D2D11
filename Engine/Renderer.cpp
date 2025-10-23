#include "pch.h"
#include "Renderer.h"
#include "GameObject.h"
#include "ConstantBufferDesc.h"
#include "Material.h"
#include "Mesh.h"
#include "Camera.h"

void Renderer::Awake()
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	{
		desc.Usage          = D3D11_USAGE_DEFAULT;
		desc.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = 0;
	}
	{
		desc.ByteWidth = sizeof(CB_PerFrame);
		Device::Instance().GetDevice()->CreateBuffer(&desc, nullptr, &_cbPerFrame);
	}
	{
		desc.ByteWidth = sizeof(CB_PerObject);
		Device::Instance().GetDevice()->CreateBuffer(&desc, nullptr, &_cbPerObject);
	}
}

void Renderer::Render()
{
	// ������ �� ������Ʈ �ؾ� �� ���
	// 1. ������� ���ε�
	CB_PerFrame perFrameData;
	{
		perFrameData.viewMatrix = Camera::ViewMatrix;
		perFrameData.projMatrix = Camera::ProjMatrix;
	}
	Device::Instance().GetContext()->UpdateSubresource(_cbPerFrame.Get(), 0, nullptr, &perFrameData, 0, 0);
	Device::Instance().GetContext()->VSSetConstantBuffers(0, 1, _cbPerFrame.GetAddressOf());


	// ������Ʈ �� ������Ʈ �ؾ� �� ���
	for(sptr<GameObject> go : _gameObjects)
	{
		// 1. ������� ���ε�
		CB_PerObject perObjectData;
		{
			perObjectData.worldMatrix = go->transform->worldMatrix;
		}
		Device::Instance().GetContext()->UpdateSubresource(_cbPerObject.Get(), 0, nullptr, &perObjectData, 0, 0);
		Device::Instance().GetContext()->VSSetConstantBuffers(1, 1, _cbPerObject.GetAddressOf());


		// 2. ��Ƽ���� ���ε� ( ���̴� + �ؽ��� ���ε� )
		auto spriteRenderer = go->GetComponent<SpriteRenderer>();
		auto material       = spriteRenderer->GetMaterial();
		material->Bind();


		// 3. �Ž� ���ε� ( ���ؽ� + �ε��� ���� ���ε� ) + ��ο� ��
		auto mesh = spriteRenderer->GetMesh();
		mesh->Bind();
	}
}

void Renderer::AddToRenderer(sptr<GameObject> gameObject)
{
	_gameObjects.push_back(gameObject);
}
