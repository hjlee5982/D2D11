#pragma once

class Renderer : public Singleton<Renderer>
{
public:
	virtual void Awake() override;
public:
	void Render();
private:
	void BindConstantBuffer();
	void RenderGameObject();
	void RenderCollider();
public:
	void AddGameObjectToRenderer(sptr<GameObject> gameObject);
	void AddColliderToRenderer(sptr<Component> collider);
private:
	List<wptr<GameObject>> _gameObjects;
	List<wptr<Component>>  _colliders;
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