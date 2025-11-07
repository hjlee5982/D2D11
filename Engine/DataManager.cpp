#include "pch.h"
#include "DataManager.h"
#include<filesystem>

namespace fs = std::filesystem;

void DataManager::Awake()
{
	for (auto& entry : fs::recursive_directory_iterator(_dataPath))
	{
		if (entry.path().extension() == ".json")
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

				// 불러온 json 뿌려주기
			}
		}
	}
}

void DataManager::ProcessJsonData(const string& rootPath, const nlohmann::json& json)
{
}
