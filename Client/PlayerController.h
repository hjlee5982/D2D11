#pragma once

class PlayerController : public Component
{
public:
	virtual void Start() override;
	virtual void Update() override;
public:
	virtual void OnCollisionEnter(sptr<BoxCollider2D> collider) override;
private:
	void MoveRight();
	void MoveLeft();
private:
	f32 _elapsed = 0.f;
	i32 _index = 1;
	sptr<class SpriteRenderer> _sr;
};

