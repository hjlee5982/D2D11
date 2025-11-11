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

		f32 obstacleWidth  = 50.f;
		f32 obstacleHeight = 300.f;

		auto topObstacle = Instantiate();
		{
			{
				topObstacle->tag = "Obstacle";
			}
			auto tf = topObstacle->AddComponent<Transform>();
			{
				tf->SetScale(Vector3(obstacleWidth, obstacleHeight, 0.f));
				tf->SetPosition(Vector3(400.f, (Global::ClientOption.height - (obstacleHeight / 2)) / 2, 0.f));
			}
			topObstacle->AddComponent<BoxCollider2D>();
			topObstacle->AddComponent<Obstacle>();
		}
		auto btmObstacle = Instantiate();
		{
			{
				btmObstacle->tag = "Obstacle";
			}
			auto tf = btmObstacle->AddComponent<Transform>();
			{
				tf->SetScale(Vector3(obstacleWidth, obstacleHeight, 0.f));
				tf->SetPosition(Vector3(400.f, -(Global::ClientOption.height - (obstacleHeight / 2)) / 2, 0.f));
			}
			btmObstacle->AddComponent<BoxCollider2D>();
			btmObstacle->AddComponent<Obstacle>();
		}
	}
}

