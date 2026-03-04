#pragma once

class SceneManager : public Singleton<SceneManager>
{
public:
	virtual void Awake() override;
public:
	void LoadScene();
	void SaveScene();
public:
	void AddScene(sptr<class Scene> scene);
	void AddGameObject(sptr<class GameObject> go);
	void AddUIObject(sptr<class GameObject> go);
public:
	void Start();
	void Update();
	void LateUpdate();
	void FixedUpdate();
private:
	List<sptr<class GameObject>> _gameObjects;
	List<sptr<class GameObject>> _uiObjects;
private:
	List<sptr<class GameObject>> _newObjects;
	List<sptr<class GameObject>> _pendingAwake;
	List<sptr<class GameObject>> _pendingStart;
private:
	List<sptr<Scene>> _scenes;
	sptr<Scene> _currentScene;
};

