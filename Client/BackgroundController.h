#pragma once

class BackgroundController : public Component
{
public:
	virtual void Start() override;
	virtual void Update() override;
public:
	Vector3 _scale;
};

