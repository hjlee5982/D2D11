#pragma once

#include "Component.h"

class UIText;

class UI_Score : public Component
{
public:
	virtual void Awake() override;
	virtual void Start() override;
private:
	void AddScore();
private:
	sptr<UIText> _scoreText;
	i32 _score = 0;
};

