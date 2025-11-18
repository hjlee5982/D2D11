#pragma once

class CollisionManager : public Singleton<CollisionManager>
{
public:
	virtual void Awake() override;
public:
	void FixedUpate();
public:
	void AddCollider(sptr<class BoxCollider2D> collider);
private:
	List<wptr<class BoxCollider2D>> _colliders;
};

