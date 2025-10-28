#pragma once

class GameObjectManager : public Singleton<GameObjectManager>
{
public:
	virtual void Awake() override;
public:
	void AddGameObject(sptr<class GameObject> go);
public:
	void Start();
	void Update();
	void LateUpdate();
private:
	List<sptr<class GameObject>> _gameObjects;
};

