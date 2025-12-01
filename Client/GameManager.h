#pragma once

#include "Component.h"

class GameManager : public Component
{
public:
	virtual void Awake() override;
private:
	bool GameOver(const struct GameOverEvent& e);
	bool AddScore(const struct AddScoreEvent& e);
private:
	i32 _score = 0;
};

