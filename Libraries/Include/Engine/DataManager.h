#pragma once

class DataManager : public Singleton<DataManager>
{
public:
	virtual void Awake() override;
private:
	void ProcessJsonData(const string& rootPath, const nlohmann::json& json);
private:
	string _dataPath = "../Data";
};

