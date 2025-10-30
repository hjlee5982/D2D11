#pragma once

class BackgroundController : public Component
{
public:
	virtual void Start() override;
	virtual void Update() override;
public:
	virtual void OnCollisionEnter(sptr<class BoxCollider2D> collider) override;
public:
	Vector3 _position;
	Vector3 _scale;
};

