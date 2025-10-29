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

	D3D11_RASTERIZER_DESC rsDesc;
	ZeroMemory(&desc, sizeof(desc));
	{
		rsDesc.FillMode      = D3D11_FILL_WIREFRAME;
		rsDesc.CullMode      = D3D11_CULL_NONE;
		rsDesc.ScissorEnable = false;
	}
	Device::Instance().GetDevice()->CreateRasterizerState(&rsDesc, _wireFrameRS.GetAddressOf());

	ZeroMemory(&desc, sizeof(desc));
	{
		rsDesc.FillMode      = D3D11_FILL_SOLID;
		rsDesc.CullMode      = D3D11_CULL_NONE;
		rsDesc.ScissorEnable = false;
	}
	Device::Instance().GetDevice()->CreateRasterizerState(&rsDesc, _defaultRS.GetAddressOf());
}

void Renderer::Render()
{
	BindConstantBuffer();
	RenderGameObject();
	RenderCollider();
}

void Renderer::BindConstantBuffer()
{
	// 프레임 당 업데이트 해야 할 요소
	// 1. 상수버퍼 바인딩
	CB_PerFrame perFrameData;
	{
		perFrameData.viewMatrix = Global::ViewMatrix;
		perFrameData.projMatrix = Global::ProjMatrix;
	}
	Device::Instance().GetContext()->UpdateSubresource(_cbPerFrame.Get(), 0, nullptr, &perFrameData, 0, 0);
	Device::Instance().GetContext()->VSSetConstantBuffers(0, 1, _cbPerFrame.GetAddressOf());
}

void Renderer::RenderGameObject()
{
	// 오브젝트 당 업데이트 해야 할 요소
	for(sptr<GameObject> go : _gameObjects)
	{
		// 1. 상수버퍼 바인딩
		CB_PerObject perObjectData;
		{
			perObjectData.worldMatrix = go->transform->GetWorldMatrix();
		}
		Device::Instance().GetContext()->UpdateSubresource(_cbPerObject.Get(), 0, nullptr, &perObjectData, 0, 0);
		Device::Instance().GetContext()->VSSetConstantBuffers(1, 1, _cbPerObject.GetAddressOf());


		// 2. 머티리얼 바인딩 ( 셰이더 + 텍스쳐 바인딩 )
		auto spriteRenderer = go->GetComponent<SpriteRenderer>();
		auto material       = spriteRenderer->GetMaterial();

		// 2-1. 와이어 프레임 설정
		if (spriteRenderer->IsWireFrame() == true)
		{
			Device::Instance().GetContext()->RSSetState(_wireFrameRS.Get());
		}
		material->Bind();


		// 3. 매시 바인딩 ( 버텍스 + 인덱스 버퍼 바인딩 ) + 드로우 콜
		auto mesh = spriteRenderer->GetMesh();
		mesh->Bind();

		// 4. 와이어 프레임 해제
		Device::Instance().GetContext()->RSSetState(_defaultRS.Get());
	}
}

void Renderer::RenderCollider()
{
}

void Renderer::AddGameObjectToRenderer(sptr<GameObject> gameObject)
{
	_gameObjects.push_back(gameObject);
}

void Renderer::AddColliderToRenderer(sptr<Component> collider)
{
}