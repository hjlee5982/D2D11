#include "pch.h"
#include "ObstacleGenerator.h"
#include "Obstacle.h"
#include "BoxCollider2D.h"

void ObstacleGenerator::Update()
{
	Generate();
}

void ObstacleGenerator::Generate()
{
	_elapsed += TIMER.DeltaTime();

	if (_elapsed >= 3.f)
	{
		std::cout << "T" << std::endl;

		_elapsed = 0.f;

		auto obstacle = Instantiate();
		{
			{
				obstacle->tag = "Obstacle";
			}
			auto tf = obstacle->AddComponent<Transform>();
			{
				tf->SetScale(Vector3(100.f, 300.f, 0.f));
				tf->SetPosition(Vector3(0.f, (Global::ClientOption.height - 150.f) / 2, 0.f));
			}
			obstacle->AddComponent<BoxCollider2D>();
			obstacle->AddComponent<Obstacle>();
		}
	}
}

