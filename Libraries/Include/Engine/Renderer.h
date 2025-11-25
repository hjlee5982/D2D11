#pragma once

class Component;
class GameObject;

class Renderer : public Singleton<Renderer>
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
	void AddGameObject(sptr<GameObject> gameObject);
	void AddCollider(sptr<Component> collider);
	void AddUI(sptr<GameObject> ui);
	void AddUIBoundary(sptr<Component> boundary);
public:
	bool colliderRendering = false;
	bool uiBoundaryRendering = false;
private:
	List<wptr<GameObject>> _gameObjects;
	List<wptr<Component>>  _colliders;
	List<wptr<GameObject>> _uis;
	List<wptr<Component>>  _boundaries;
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