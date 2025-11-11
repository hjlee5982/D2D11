#pragma once

class Scene abstract : public Object
{
public:
	Scene() {}
	Scene(const string& sceneName) { name = sceneName; }
public:
	virtual void Awake() abstract;
public:
	void AddGameObject(wptr<class GameObject> go);
public:
	List<wptr<IJson>> GetGameObjects();
private:
	List<wptr<IJson>> _gameObjects;
};

