#pragma once

class Scene;

class SceneManager : public Singleton<SceneManager>
{
public:
	virtual void Awake() override;
public:
	void LoadScene();
	void SaveScene();
public:
	void AddGameObject(wptr<class GameObject> go);
private:
	List<sptr<Scene>> _scenes;
	sptr<Scene> _currentScene;
private:
	List<wptr<IJson>> _goInScene;
};

