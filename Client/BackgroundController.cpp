#include "pch.h"
#include "BackgroundController.h"

void BackgroundController::Start()
{
	Owner()->transform->SetScale(_scale);
	Owner()->transform->SetPosition(_position);
}

void BackgroundController::Update()
{
	Owner()->transform->Translation(Vector3::Right, 10.f);
}

void BackgroundController::OnCollisionEnter(sptr<class BoxCollider2D> collider)
{
	sptr<int> t;
}
