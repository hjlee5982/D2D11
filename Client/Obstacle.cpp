#include "pch.h"
#include "Obstacle.h"

void Obstacle::Update()
{
	Owner()->transform->Translation(-Vector3::Right, 300.f * TIMER.DeltaTime());
}
