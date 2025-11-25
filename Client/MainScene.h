#pragma once

#include "Scene.h"

class MainScene : public Scene
{
public:
	void Awake() override;
public:
	void LoadResources();
	void SetInputSystem();
	void AddGameObject();
	void AddUIObject();
	void EngineSetting();
};