#include "pch.h"
#include "BackgroundController.h"

void BackgroundController::Awake()
{
	int a = 0;
}

void BackgroundController::Start()
{
	int a = 0;

}

void BackgroundController::Update()
{
	gameObject->transform->Translation(-Vector3::Right, 150.f);
}

void BackgroundController::LateUpdate()
{
	int a = 0;
}
