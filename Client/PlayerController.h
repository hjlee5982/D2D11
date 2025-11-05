#pragma once

class PlayerController : public Component
{
public:
	virtual void Start()       override;
	virtual void Update()      override;
public:
	virtual void OnCollisionEnter(sptr<BoxCollider2D> collider) override;
private:
	void Jump();
private:
	void TempAnimation();
private:
	bool _trigger = false;
	f32 _velocity = 5.f;
	f32 _elapsed = 0.f;
	i32 _index = 1;
	sptr<class SpriteRenderer> _sr;
	void ToggleConsole();
	void OpenConsole();
	void CloseConsole();
	bool _isConsoleOpen = false;
};

