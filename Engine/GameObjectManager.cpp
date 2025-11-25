#include "pch.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "Camera.h"

void GameObjectManager::AddGameObject(sptr<class GameObject> go)
{
	_newObjects.push_back(go);
}

void GameObjectManager::AddUIObject(sptr<class GameObject> go)
{
	_uiObject.push_back(go);
}

void GameObjectManager::Awake()
{
	auto go = Instantiate();
	{
		go->AddComponent<Transform>();
		auto camera = go->AddComponent<Camera>();
		{
			CameraDesc desc;
			{
				desc.Type = ProjectionType::OrthoUI;
			}
			camera->Initialize(desc);
		}
	}

	for (auto& ui : _uiObject)
	{
		ui->Awake();
	}
}

void GameObjectManager::Start()
{
	for (auto& ui : _uiObject)
	{
		ui->Start();
	}
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
		if (go->isActive == true)
		{
			go->Update();
		}
	}

	for (auto& ui : _uiObject)
	{
		ui->Update();
	}
}

void GameObjectManager::LateUpdate()
{
	for (auto& go : _gameObjects)
	{
		if (go->isActive == true)
		{
			go->LateUpdate();
		}
	}

	for (auto& ui : _uiObject)
	{
		ui->LateUpdate();
	}
}

void GameObjectManager::FixedUpdate()
{
	for (auto& go : _gameObjects)
	{
		if (go->isActive == true)
		{
			go->FixedUpdate();
		}
	}

	for (auto& ui : _uiObject)
	{
		ui->FixedUpdate();
	}
}
