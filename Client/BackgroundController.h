#pragma once

class BackgroundController : public Component
{
	REFLECTION_COMPONENT(BackgroundController);
public:
	virtual void Start() override;
	virtual void Update() override;
	virtual void FixedUpdate() override;
public:
	Vector3 _scale;
};

