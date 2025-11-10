#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Renderer.h"

namespace fs = std::filesystem;

void SceneManager::Awake()
{
	Dictionary<string, nlohmann::json> config;

	// config.json에 기록되어 있는 마지막에 활성화 되어있던 씬을 불러옴
	for (auto& entry : fs::recursive_directory_iterator("../Data/Scene"))
	{
		std::ifstream file(entry.path());

		if (file.is_open() == false)
		{
			continue;
		}
		else
		{
			nlohmann::json json;
			file >> json;

			string fileName = entry.path().stem().string();

			config[fileName] = json;
		}
	}

	string currentSceneName = config.find("config")->second.at("CurrentSceneName");

	nlohmann::json json = config.find(currentSceneName)->second;

	/*_currentScene = std::static_pointer_cast<Scene>(ObjectFactory::Create(json["SceneName"]));
	_scenes.push_back(_currentScene);*/

	for (auto& goJson : json["GameObjects"])
	{
		auto go = makeSptr<GameObject>(goJson.at("Name"));

		for (auto& comJson : goJson["Components"])
		{
			auto com = std::static_pointer_cast<Component>(ObjectFactory::Create(comJson["Type"]));

			com->LoadJson(comJson);

			go->AddComponent(com);

			GAMEOBJECT.AddGameObject(go);
			RENDERER.AddGameObject(go);
		}
	}
}

void SceneManager::SaveScene()
{
	//// 현재 활성화 된 씬이 뭔지 기록하기 위함
	//{
	//	nlohmann::json configJson;
	//	configJson["CurrentScene"] = _currentScene->_name;

	//	std::ofstream file("../Data/Scene/config.json");
	//	file << configJson.dump(4);
	//	file.close();
	//}
	//// 현재 씬에 있는 모든 오브젝트, 그 오브젝트의 컴포넌트를 모두 기록
	//{
	//	nlohmann::json sceneJson;
	//	sceneJson["SceneName"] = _currentScene->_name;

	//	for (auto& goInScene : _currentScene->GetObjInScene())
	//	{
	//		if (auto go = goInScene.lock())
	//		{
	//			go->MakeJson();
	//			sceneJson["GameObjects"].push_back(go->_json);
	//		}
	//	}

	//	std::ofstream file("../Data/" + _currentScene->_name + ".json");
	//	file << sceneJson.dump(4);
	//	file.close();
	//}
}

void SceneManager::AddGameObject(wptr<class GameObject> go)
{
	if (_currentScene != nullptr)
	{
		_currentScene->AddGameObject(go);
	}
}

