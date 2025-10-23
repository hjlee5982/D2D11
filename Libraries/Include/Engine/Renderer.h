#pragma once

class Renderer : public Singleton<Renderer>
{
public:
	virtual void Awake() override;
public:
	void Render();
public:
	void AddToRenderer(sptr<GameObject> gameObject);
private:
	List<sptr<class GameObject>> _gameObjects;
private:
	ComPtr<ID3D11Buffer> _cbPerFrame;
	ComPtr<ID3D11Buffer> _cbPerObject;
};

