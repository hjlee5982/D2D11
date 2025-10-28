#include "pch.h"
#include "GameObjectManager.h"

void GameObjectManager::Awake()
{
	// 기본 카메라 생성
	auto camera = Instantiate();
	{
		camera->AddComponent<Camera>();
	}
	AddGameObject(camera);

	for (auto& go : _gameObjects)
	{
		go->Awake();
	}
}

void GameObjectManager::AddGameObject(sptr<class GameObject> go)
{
	_gameObjects.push_back(go);
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
}

void GameObjectManager::LateUpdate()
{
	for (auto& go : _gameObjects)
	{
		go->LateUpdate();
	}
}
