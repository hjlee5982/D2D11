#pragma once


#include "RenderCommand.h"


class Renderer;
class Component;
class Collider;
class GameObject;
class UIComponent;
class SpriteRenderPass;

class RenderManager : public Singleton<RenderManager>
{
public:
	virtual void Awake() override;
public:
	void Render();
private:
	void RenderGameObject();
	void RenderCollider();
	void RenderUI();
	void RenderUIBoundary();
public:
	void AddRenderer(sptr<Renderer> renderer);
	void AddCollider(sptr<Collider> collider);
	void AddUI(sptr<UIComponent> ui);
public:
	bool colliderRendering   = false;
	bool uiBoundaryRendering = false;
private:
	List<wptr<Renderer>>    _renderers;
	List<wptr<Collider>>    _colliders;
	List<wptr<UIComponent>> _uis;
private:
	sptr<SpriteRenderPass> _spritePass;
private:
	ComPtr<ID3D11Buffer> _cbPerFrame;
	ComPtr<ID3D11Buffer> _cbPerObject;
private:
	ComPtr<ID3D11RasterizerState> _wireFrameRS;
	ComPtr<ID3D11RasterizerState> _defaultRS;
private:
	ComPtr<ID3D11DepthStencilState> _dss;
private:
	ComPtr<ID3D11BlendState> _bs;
};