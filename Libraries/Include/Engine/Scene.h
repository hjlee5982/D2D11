#pragma once

class Scene abstract : public IJson
{
public:
	Scene(const string& sceneName)
	{
		_name = sceneName;
	}
public:
	virtual void InitializeScene() abstract;
private:
	string _name;
};

