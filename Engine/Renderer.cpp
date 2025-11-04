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
	// 상수 버퍼 생성
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	{
		desc.Usage          = D3D11_USAGE_DEFAULT;
		desc.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = 0;
	}
	{
		desc.ByteWidth = sizeof(CB_PerFrame);
		DEVICE->CreateBuffer(&desc, nullptr, &_cbPerFrame);
	}
	{
		desc.ByteWidth = sizeof(CB_PerObject);
		DEVICE->CreateBuffer(&desc, nullptr, &_cbPerObject);
	}

	// 와이어 프레임 레스터라이저 생성
	D3D11_RASTERIZER_DESC rsDesc;
	ZeroMemory(&desc, sizeof(desc));
	{
		rsDesc.FillMode      = D3D11_FILL_WIREFRAME;
		rsDesc.CullMode      = D3D11_CULL_NONE;
		rsDesc.ScissorEnable = false;
	}
	DEVICE->CreateRasterizerState(&rsDesc, _wireFrameRS.GetAddressOf());

	// 기본 레스터라이저 생성
	ZeroMemory(&desc, sizeof(desc));
	{
		rsDesc.FillMode      = D3D11_FILL_SOLID;
		rsDesc.CullMode      = D3D11_CULL_NONE;
		rsDesc.ScissorEnable = false;
	}
	DEVICE->CreateRasterizerState(&rsDesc, _defaultRS.GetAddressOf());

	// DS스테이트 생성
	D3D11_DEPTH_STENCIL_DESC dsDesc;
	ZeroMemory(&dsDesc, sizeof(dsDesc));
	{
		dsDesc.DepthEnable    = false;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDesc.DepthFunc      = D3D11_COMPARISON_ALWAYS;
	}
	DEVICE->CreateDepthStencilState(&dsDesc, _dss.GetAddressOf());

	// 블랜드 스테이트 생성
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));
	{
		blendDesc.RenderTarget[0].BlendEnable			= TRUE;
		blendDesc.RenderTarget[0].SrcBlend				= D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend				= D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOp				= D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha			= D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha		= D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOpAlpha			= D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	}
	DEVICE->CreateBlendState(&blendDesc, _bs.GetAddressOf());


	// 2D게임은 깊이테스트를 꺼야 추가 한 순서대로 그려짐
	CONTEXT->OMSetDepthStencilState(_dss.Get(), 0);

	// 2D는 블랜드를 켜줘야 함
	CONTEXT->OMSetBlendState(_bs.Get(), nullptr, 0xffffffff);
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
	CONTEXT->UpdateSubresource(_cbPerFrame.Get(), 0, nullptr, &perFrameData, 0, 0);
	CONTEXT->VSSetConstantBuffers(0, 1, _cbPerFrame.GetAddressOf());
}

void Renderer::RenderGameObject()
{
	SortedDictionary<int, List<sptr<GameObject>>> orderInLayer;

	for (auto& go : _gameObjects)
	{
		auto renderer = go->GetComponent<SpriteRenderer>();

		orderInLayer[renderer->OrderInLayer].push_back(go);
	}

	for (auto& kvp : orderInLayer)
	{
		for (auto& go : kvp.second)
		{
			// 1. 상수버퍼 바인딩
			CB_PerObject perObjectData;
			{
				perObjectData.worldMatrix = go->transform->GetWorldMatrix();
			}
			CONTEXT->UpdateSubresource(_cbPerObject.Get(), 0, nullptr, &perObjectData, 0, 0);
			CONTEXT->VSSetConstantBuffers(1, 1, _cbPerObject.GetAddressOf());


			// 2. 머티리얼 바인딩 ( 셰이더 + 텍스쳐 바인딩 )
			auto spriteRenderer = go->GetComponent<SpriteRenderer>();
			auto material = spriteRenderer->GetMaterial();
			material->Bind();


			// 3. 매시 바인딩 ( 버텍스 + 인덱스 버퍼 바인딩 ) + 드로우 콜
			auto mesh = spriteRenderer->GetMesh();
			mesh->Bind();
		}
	}
}

void Renderer::RenderCollider()
{
	// 콜라이더는 와이어 프레임
	CONTEXT->RSSetState(_wireFrameRS.Get());

	// 콜라이더는 일반 물체와 그리는 법이 달라서 토폴로지를 따로 설정해줘야 함
	CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	// 오브젝트 당 업데이트 해야 할 요소
	for (sptr<Component>& go : _colliders)
	{
		auto collider = go->Owner()->GetComponent<BoxCollider2D>();
		// 1. 상수버퍼 바인딩
		CB_PerObject perObjectData;
		{
			perObjectData.worldMatrix = collider->GetColliderTransform()->GetWorldMatrix();
		}
		CONTEXT->UpdateSubresource(_cbPerObject.Get(), 0, nullptr, &perObjectData, 0, 0);
		CONTEXT->VSSetConstantBuffers(1, 1, _cbPerObject.GetAddressOf());


		// 2. 머티리얼 바인딩 ( 셰이더 + 텍스쳐 바인딩 )
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

		CONTEXT->IASetVertexBuffers(vb->GetSlot(), 1, vb->GetVertexBuffer().GetAddressOf(), &stride, &offset);
		CONTEXT->IASetIndexBuffer(ib->GetIndexBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);

		// 드로우콜
		CONTEXT->DrawIndexed(icount, 0, 0);
	}

	// 와이어 프레임 해제
	CONTEXT->RSSetState(_defaultRS.Get());

	// 토폴로지 원상복구
	CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Renderer::AddGameObjectToRenderer(sptr<GameObject> gameObject)
{
	_gameObjects.push_back(gameObject);
}

void Renderer::AddColliderToRenderer(sptr<Component> collider)
{
	_colliders.push_back(collider);
}