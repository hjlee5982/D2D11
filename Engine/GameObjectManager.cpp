#include "pch.h"
#include "GameObjectManager.h"

void GameObjectManager::AddGameObject(sptr<class GameObject> go)
{
	_newObjects.push_back(go);
}

void GameObjectManager::Update()
{
	for (auto& go : _newObjects)
	{
		_pendingAwake.push_back(go);
	}
	_newObjects.clear();


	for (auto& go : _pendingAwake)
	{
		go->Awake();
	}
	_pendingStart.insert(_pendingStart.end(), _pendingAwake.begin(), _pendingAwake.end());
	_pendingAwake.clear();


	for (auto& go : _pendingStart)
	{
		go->Start();
	}
	for (auto& go : _pendingStart)
	{
		_gameObjects.push_back(go);
	}
	_pendingStart.clear();


	for (auto& go : _gameObjects)
	{
		go->Update();
	}
}

void GameObjectManager::LateUpdate()
{
	for (auto& go : _gameObjects)
	{
		go->LateUpdate();
	}
}

void GameObjectManager::FixedUpdate()
{
	for (auto& go : _gameObjects)
	{
		go->FixedUpdate();
	}
}
