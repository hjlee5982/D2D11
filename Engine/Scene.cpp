#include "pch.h"
#include "Scene.h"
#include "Transform.h"
#include "Camera.h"

void Scene::AddGameObject(sptr<class GameObject> go)
{
	_newObjects.push_back(go);
}

void Scene::Awake()
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
}

void Scene::Start()
{
}

void Scene::Update()
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
		_gameObjects.push_back(go);
	}
	for (auto& go : _pendingStart)
	{
		go->Start();
	}
	_pendingStart.clear();


	for (auto& go : _gameObjects)
	{
		if (go->isActive == true)
		{
			go->Update();
		}
	}

	for (auto& go : _destroyObjects)
	{
		_gameObjects.erase(remove(_gameObjects.begin(), _gameObjects.end(), go), _gameObjects.end());
	}
	_destroyObjects.clear();
}

void Scene::LateUpdate()
{
	for (auto& go : _gameObjects)
	{
		if (go->isActive == true)
		{
			go->LateUpdate();
		}
	}
}

void Scene::FixedUpdate()
{
	for (auto& go : _gameObjects)
	{
		if (go->isActive == true)
		{
			go->FixedUpdate();
		}
	}
}

void Scene::Destroy(sptr<class GameObject> go)
{
	_destroyObjects.push_back(go);
}
