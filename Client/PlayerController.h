#pragma once

class PlayerController : public Component
{
public:
	virtual void Start() override;
	virtual void Update() override;
public:
	virtual void OnCollisionEnter(sptr<BoxCollider2D> collider) override;
};

