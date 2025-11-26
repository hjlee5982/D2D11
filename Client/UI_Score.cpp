#include "pch.h"
#include "UI_Score.h"
#include "InputSystem.h"
#include "UIText.h"
#include <format>
#include "Event.h"
#include "EventManager.h"

void UI_Score::Awake()
{
	_scoreText = Owner()->GetComponent<UIText>();

	EVENT::Subscribe<AddScoreEvent>(&UI_Score::AddScore, this);
}

bool UI_Score::AddScore(const AddScoreEvent& e)
{
	++_score;

	wstring wstr = std::format(L"{:03}", _score);
	
	_scoreText->Text(wstr);

	return true;
}