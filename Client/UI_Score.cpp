#include "pch.h"
#include "UI_Score.h"
#include "InputSystem.h"
#include "UIText.h"
#include <format>
#include "EventManager.h"

void UI_Score::Awake()
{
	_scoreText = Owner()->GetComponent<UIText>();
}

void UI_Score::Start()
{
	INPUT.FindAction("AddScore")->started = std::bind(&UI_Score::AddScore, this);
}

void UI_Score::AddScore()
{
	/*++_score;

	wstring wstr = std::format(L"{:03}", _score);
	
	_scoreText->Text(wstr);*/

	LOG_INFO("이벤트 송신");

	EVENT::SendEvent(StartGenerateEvent{});
}
