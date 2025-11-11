#include "pch.h"
#include "Scene.h"
#include "GameObject.h"

void Scene::AddGameObject(wptr<GameObject> go)
{
	_gameObjects.push_back(go);
}

List<wptr<IJson>> Scene::GetGameObjects()
{
	return _gameObjects;
}