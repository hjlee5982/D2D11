#include "pch.h"
#include "BackgroundController.h"

void BackgroundController::Start()
{
	_scale = Owner()->transform->GetScale();
}

void BackgroundController::Update()
{
	auto position = Owner()->transform->GetPosition();

	position.x -= 300.f * TIMER.DeltaTime();

	if (position.x <= -2200.f)
	{
		position.x += 2200.f * 2.f;
	}

	Owner()->transform->SetPosition(position);
}

void BackgroundController::FixedUpdate()
{
	
}
