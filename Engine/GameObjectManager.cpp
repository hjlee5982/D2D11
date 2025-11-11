#include "pch.h"
#include "GameObjectManager.h"

void GameObjectManager::AddGameObject(sptr<class GameObject> go)
{
	_gameObjects.push_back(go);
}

void GameObjectManager::AddLiveGameObject(sptr<class GameObject> go)
{
	_spawnList.push_back(go);
}

void GameObjectManager::Awake()
{
	for (auto& go : _gameObjects)
	{
		go->Awake();
	}
}

void GameObjectManager::Start()
{
	for (auto& go : _gameObjects)
	{
		go->Start();
	}
}

void GameObjectManager::Update()
{
	for (auto& go : _gameObjects)
	{
		go->Update();
	}

	for (auto& go : _spawnList)
	{
		go->Awake();
		go->Start();
		_gameObjects.push_back(go);
	}
	_spawnList.clear();
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
