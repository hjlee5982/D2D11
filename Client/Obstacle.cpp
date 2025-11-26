#include "pch.h"
#include "Obstacle.h"
#include "ObstacleGenerator.h"
#include "GameObject.h"
#include "Transform.h"

void Obstacle::Update()
{
	Owner()->transform->Translation(-Vector3::Right, _speed *TIMER.DeltaTime());

	auto position = Owner()->transform->GetPosition();

	if (position.x <= -4.f)
	{
		_isColliding = false;
		_generator.lock()->ReturnPool(Owner());
	}
}
