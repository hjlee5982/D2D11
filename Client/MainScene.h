#pragma once

class MainScene : public Scene
{
	REFLECTION(MainScene);
public:
	void Awake() override;
public:
	void LoadResources();
	void SetInputSystem();
	void AddGameObject();
	void AddUIObject();
	void EngineSetting();
};