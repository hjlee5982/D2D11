#include "pch.h"
#include "GameManager.h"
#include "Event.h"
#include "EventManager.h"
#include "Timer.h"
#include "InputSystem.h"

void GameManager::Awake()
{
	EVENT::Subscribe<GameOverEvent>(&GameManager::GameOver, this);
	EVENT::Subscribe<AddScoreEvent>(&GameManager::AddScore, this);

	INPUT.FindAction("Time")->started = std::bind(&GameManager::TimeScale, this);
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

void GameManager::TimeScale()
{
	TIMER._timeScale == 1.f ? TIMER._timeScale = 0.f : TIMER._timeScale = 1.f;
}
