#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"

#include "TestScene.h"
#include "TestGameObject.h"
#include "TypeRegistry.h"

namespace fs = std::filesystem;

void SceneManager::Awake()
{
	_currentScene.lock()->Initialize();
	_currentScene.lock()->Awake();
}

void SceneManager::LoadScene()
{
}

void SceneManager::SaveScene()
{
}

void SceneManager::AddScene(const string& name, sptr<class Scene> scene)
{
	_scenes[name] = scene;

	_currentScene = scene;
}

void SceneManager::AddGameObject(sptr<class GameObject> go)
{
	_currentScene.lock()->AddGameObject(go);
}

void SceneManager::AddTestScene(TestScene* scene)
{
	_currentTestScene = scene;
}

TestScene* SceneManager::GetCurrentScene()
{
	return _currentTestScene;
}

void SceneManager::Start()
{
	_currentScene.lock()->Start();
}

void SceneManager::Update()
{
	_currentScene.lock()->Update();
}

void SceneManager::LateUpdate()
{
	_currentScene.lock()->LateUpdate();
}

void SceneManager::FixedUpdate()
{
	_currentScene.lock()->FixedUpdate();
}

void SceneManager::Destroy(sptr<GameObject> go)
{
	_currentScene.lock()->Destroy(go);
}

