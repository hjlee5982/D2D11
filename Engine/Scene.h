#pragma once

class Scene abstract : public Object
{
public:
	Scene() {}
	Scene(const string& sceneName)
	{
		_name = sceneName;
	}
public:
	virtual void InitializeScene() abstract;
public:
	void AddGameObject(wptr<class GameObject> go)
	{
		_goInScene.push_back(go);
	}
public:
	List<wptr<IJson>> GetObjInScene()
	{
		return _goInScene;
	}
public:
	string _name;
private:
	List<wptr<IJson>> _goInScene;
};

