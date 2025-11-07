#pragma once

class DataManager : public Singleton<DataManager>
{
public:
	virtual void Awake() override;
private:
	string _dataPath = "../Data";
};

