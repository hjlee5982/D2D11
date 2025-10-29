#include "pch.h"
#include "Renderer.h"
#include "GameObject.h"
#include "ConstantBufferDesc.h"
#include "Material.h"
#include "Mesh.h"
#include "Camera.h"
#include "BoxCollider2D.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

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
		material->Bind();


		// 3. 매시 바인딩 ( 버텍스 + 인덱스 버퍼 바인딩 ) + 드로우 콜
		auto mesh = spriteRenderer->GetMesh();
		mesh->Bind();
	}
}

void Renderer::RenderCollider()
{
	// 콜라이더는 와이어 프레임
	Device::Instance().GetContext()->RSSetState(_wireFrameRS.Get());

	// 콜라이더는 일반 물체와 그리는 법이 달라서 토폴로지를 따로 설정해줘야 함
	Device::Instance().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	// 오브젝트 당 업데이트 해야 할 요소
	for (sptr<Component> go : _colliders)
	{
		// 1. 상수버퍼 바인딩
		CB_PerObject perObjectData;
		{
			perObjectData.worldMatrix = go->Owner()->transform->GetWorldMatrix();
		}
		Device::Instance().GetContext()->UpdateSubresource(_cbPerObject.Get(), 0, nullptr, &perObjectData, 0, 0);
		Device::Instance().GetContext()->VSSetConstantBuffers(1, 1, _cbPerObject.GetAddressOf());


		// 2. 머티리얼 바인딩 ( 셰이더 + 텍스쳐 바인딩 )
		auto collider = go->Owner()->GetComponent<BoxCollider2D>();
		auto material = collider->GetMaterial();
		material->Bind();


		// 3. 매시 바인딩 ( 버텍스 + 인덱스 버퍼 바인딩 ) + 드로우 콜
		// 매시서 바로 바인드 땡기면 안됨, 직접 vb, ib 바인드 하고 드로우콜 해야됨
		auto mesh = collider->GetMesh();
		
		sptr<VertexBuffer> vb = mesh->GetVertexBuffer();
		sptr<IndexBuffer>  ib = mesh->GetIndexBuffer();

		u32 stride = vb->GetStride();
		u32 offset = vb->GetOffset();
		u32 icount = ib->GetIndexCount();

		Device::Instance().GetContext()->IASetVertexBuffers(vb->GetSlot(), 1, vb->GetVertexBuffer().GetAddressOf(), &stride, &offset);
		Device::Instance().GetContext()->IASetIndexBuffer(ib->GetIndexBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);

		// 드로우콜
		Device::Instance().GetContext()->DrawIndexed(icount, 0, 0);
	}

	// 와이어 프레임 해제
	Device::Instance().GetContext()->RSSetState(_defaultRS.Get());

	// 토폴로지 원상복구
	Device::Instance().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Renderer::AddGameObjectToRenderer(sptr<GameObject> gameObject)
{
	_gameObjects.push_back(gameObject);
}

void Renderer::AddColliderToRenderer(sptr<Component> collider)
{
	_colliders.push_back(collider);
}