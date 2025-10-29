#pragma once

class CollisionManager : public Singleton<CollisionManager>
{
public:
	virtual void Awake() override;
public:
	void Update();
public:
	void AddCollider(sptr<class BoxCollider2D> collider);
private:
	List<sptr<class BoxCollider2D>> _colliders;
};

