#pragma once

class BackgroundController : public Component
{
public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
public:
	Vector3 _position;
	Vector3 _scale;
};

