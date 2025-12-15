#include "pch.h"
#include "RenderPass.h"
#include "ConstantBufferDesc.h"
#include "RenderCommand.h"
#include "Material.h"
#include "Shader.h"
#include "TMesh.h"

void SpriteRenderPass::Init()
{

	// 상수 버퍼 생성
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	{
		desc.Usage          = D3D11_USAGE_DEFAULT;
		desc.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = 0;
		desc.ByteWidth      = sizeof(CB_PerObject);
	}
	DEVICE->CreateBuffer(&desc, nullptr, &_cbPerObject);
}

void SpriteRenderPass::Bind(RenderContext& ctx)
{
	// 정렬
	std::sort(ctx.spriteCmds.begin(), ctx.spriteCmds.end(),
		[](auto& a, auto& b)
		{
			return a.OrderInLayer < b.OrderInLayer;
		});


	// 바인딩
	for (auto& cmd : ctx.spriteCmds)
	{
		// 1. 상수버퍼 바인딩
		CB_PerObject perObjectData;
		{
			perObjectData.worldMatrix = cmd.WorldMatrix;
		}
		CONTEXT->UpdateSubresource(_cbPerObject.Get(), 0, nullptr, &perObjectData, 0, 0);
		CONTEXT->VSSetConstantBuffers(1, 1, _cbPerObject.GetAddressOf());

		// 2. 머티리얼 바인딩 ( 셰이더 + 텍스쳐 )
		cmd.Material->Bind();

		// 3. 매시 바인딩 ( VI버퍼 바인딩 + 인풋레이아웃 설정 ) + 드로우 콜
		cmd.Mesh->Bind(cmd.Material->GetShader());
	}
}
