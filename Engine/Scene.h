#pragma once

#include "IReflection.h"

class Scene abstract : public IReflection
{
public:
	virtual void Awake() abstract;
public:
	void AddGameObject(wptr<class GameObject> go);
public:
	List<wptr<IJson>> GetGameObjects();
private:
	List<wptr<IJson>> _gameObjects;
};

