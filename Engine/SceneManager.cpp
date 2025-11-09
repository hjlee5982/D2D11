#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"

void SceneManager::Awake()
{
	LoadScene();
}

void SceneManager::LoadScene()
{
	// 임시로 여기에 담아놨음
	// Global::ClientOption.scene

	_currentScene = Global::ClientOption.scene;
}

void SceneManager::SaveScene()
{
	nlohmann::json sceneJson;
	sceneJson["SceneName"] = "MainScene";

	for (auto& goInScene : _goInScene)
	{
		if (auto go = goInScene.lock())
		{
			go->MakeJson();
			sceneJson["GameObjects"].push_back(go->_json);
		}
	}

	_currentScene->_json = sceneJson;

	string sceneName = "MainScene";

	std::ofstream file("../Data/" + sceneName + ".json");
	file << _currentScene->_json.dump(4);
	file.close();
}

void SceneManager::AddGameObject(wptr<class GameObject> go)
{
	_goInScene.push_back(go);
}
