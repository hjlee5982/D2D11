#pragma once

class BackgroundController : public Component
{
public:
	virtual void Start() override;
	virtual void Update() override;
	virtual void FixedUpdate() override;
public:
	Vector3 _scale;
};

