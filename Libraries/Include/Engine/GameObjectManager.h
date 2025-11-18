#pragma once

class GameObjectManager : public Singleton<GameObjectManager>
{
public:
	virtual void Awake() override;
public:
	void AddGameObject(sptr<class GameObject> go);
	void AddLiveGameObject(sptr<class GameObject> go);
public:
	void Start();
	void Update();
	void LateUpdate();
	void FixedUpdate();
private:
	List<sptr<class GameObject>> _gameObjects;
private:
	// Update에서 생성된 오브젝트 리스트
	List<sptr<class GameObject>> _spawnList;

private:
	List<sptr<class GameObject>> _newObjects;
	List<sptr<class GameObject>> _pendingAwake;
	List<sptr<class GameObject>> _pendingStart;

	bool a = false;
	bool s = false;
};

