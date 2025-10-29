#include "pch.h"
#include "BackgroundController.h"

void BackgroundController::Awake()
{
}

void BackgroundController::Start()
{
	Owner()->transform->SetScale(_scale);
	Owner()->transform->SetPosition(_position);
}

void BackgroundController::Update()
{
	Owner()->transform->Translation(Vector3::Right, 10.f);
}

void BackgroundController::LateUpdate()
{
}
