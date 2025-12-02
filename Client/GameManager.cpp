#include "pch.h"
#include "GameManager.h"
#include "Event.h"
#include "EventManager.h"
#include "Timer.h"

void GameManager::Awake()
{
	EVENT::Subscribe<GameOverEvent>(&GameManager::GameOver, this);
	EVENT::Subscribe<AddScoreEvent>(&GameManager::AddScore, this);
}

bool GameManager::GameOver(const GameOverEvent& e)
{
	TIMER.TimeScale(0.f);

	return false;
}

bool GameManager::AddScore(const AddScoreEvent& e)
{
	++_score;

	EVENT::SendEvent(RefreshUIEvent{ _score });

	return false;
}
