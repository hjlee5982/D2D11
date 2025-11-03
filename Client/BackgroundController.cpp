#include "pch.h"
#include "BackgroundController.h"

void BackgroundController::Start()
{
	_scale = Owner()->transform->GetScale();
}

void BackgroundController::Update()
{
	/*Owner()->transform->Translation(-Vector3::Right, 200.f);

	if (Owner()->transform->GetPosition().x <= -_scale.x)
	{
		Owner()->transform->SetPosition(Vector3(_scale.x, 0.f, 0.f));
	}*/
}