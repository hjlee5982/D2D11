#pragma once

#include "Scene.h"

class MainScene : public Scene
{
public:
	virtual void Initialize() override;
public:
	void LoadResources();
	void SetInputSystem();
	void AddGameObject();
	void EngineSetting();
};