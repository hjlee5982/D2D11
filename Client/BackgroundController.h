#pragma once

class BackgroundController : public Component
{
	REFLECTION(BackgroundController);
public:
	virtual void Start() override;
	virtual void Update() override;
	virtual void FixedUpdate() override;
private:
	sptr<class GameObject> _bg1;
	sptr<class GameObject> _bg2;
private:
	f32 _bgSpeed = 2.5f;
	f32 _scale = 0.f;
};

