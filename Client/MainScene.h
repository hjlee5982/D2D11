#pragma once

class MainScene : public Scene
{
	REFLECTION(MainScene);
public:
	MainScene() {}
	MainScene(const string& sceneName) : Scene(sceneName) {}
public:
	void Awake() override;
public:
	void LoadResources();
	void SetInputSystem();
	void AddGameObject();
};