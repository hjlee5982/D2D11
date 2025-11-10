#pragma once

class BackgroundController : public Component
{
	REFLECTION(BackgroundController);
public:
	virtual void Start() override;
	virtual void Update() override;
	virtual void FixedUpdate() override;
public:
	Vector3 _scale;
};

