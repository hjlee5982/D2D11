#pragma once

class GameObjectManager : public Singleton<GameObjectManager>
{
public:
	void AddGameObject(sptr<class GameObject> go);
public:
	void Update();
	void LateUpdate();
	void FixedUpdate();
private:
	List<sptr<class GameObject>> _gameObjects;
private:
	List<sptr<class GameObject>> _newObjects;
	List<sptr<class GameObject>> _pendingAwake;
	List<sptr<class GameObject>> _pendingStart;
};

