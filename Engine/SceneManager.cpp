#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "RenderManager.h"

namespace fs = std::filesystem;

void SceneManager::Awake()
{
	_currentScene->Awake();
}

void SceneManager::LoadScene()
{
}

void SceneManager::SaveScene()
{

}

void SceneManager::AddScene(sptr<class Scene> scene)
{
	_currentScene = scene;

	_scenes.push_back(scene);
}

void SceneManager::AddGameObject(sptr<class GameObject> go)
{
	if (_currentScene != nullptr)
	{
		_currentScene->AddGameObject(go);
	}
}

void SceneManager::AddUIObject(sptr<class GameObject> go)
{

}

void SceneManager::Start()
{
}

void SceneManager::Update()
{
}

void SceneManager::LateUpdate()
{
}

void SceneManager::FixedUpdate()
{
}

