#pragma once

class IRenderPass
{
public:
	virtual void Init() = 0;
	virtual void Bind(struct RenderContext& ctx) = 0;
protected:
	ComPtr<ID3D11Buffer> _cbPerObject;
};


class SpriteRenderPass : public IRenderPass
{
public:
	virtual void Init() override;
	virtual void Bind(struct RenderContext& ctx) override;
};