#include "pch.h"
#include "ObstacleGenerator.h"
#include "Obstacle.h"
#include "BoxCollider2D.h"
#include "AssetManager.h"
#include "SpriteRenderer.h"
#include "Texture.h"

void ObstacleGenerator::Update()
{
	Generate();
}

void ObstacleGenerator::Generate()
{
	_elapsed += TIMER.DeltaTime();

	if (_elapsed >= 3.f)
	{
		_elapsed = 0.f;

		f32 obstacleWidth  = 50.f;
		f32 obstacleHeight = 200.f;

		auto topObstacle = Instantiate();
		{
			{
				topObstacle->tag = "Obstacle";
			}
			auto tf = topObstacle->AddComponent<Transform>();
			{
				tf->SetScale(Vector3(obstacleWidth, obstacleHeight, 1.f));
				tf->SetPosition(Vector3(400.f, (Global::ClientOption.height - (obstacleHeight)) / 2, 0.f));
			}
			
			topObstacle->AddComponent<BoxCollider2D>();
			topObstacle->AddComponent<Obstacle>();

			auto cloud = Instantiate();
			{
				auto cloudTf = cloud->AddComponent<Transform>();
				{
					cloudTf->SetParent(tf);
					cloudTf->SetScale(Vector3(100.f, 75.f, 1.f));
					cloudTf->SetLocalPosition(Vector3(0.f,- 0.5f, 0.f));
				}
				auto sr = cloud->AddComponent<SpriteRenderer>();
				{
					sr->SetTexture(ASSET.Get<Texture>(L"Texture_Cloud"));
					sr->OrderInLayer = 15;
				}
				cloud->AddComponent<BoxCollider2D>();
			}
		}
		auto btmObstacle = Instantiate();
		{
			{
				btmObstacle->tag = "Obstacle";
			}
			auto tf = btmObstacle->AddComponent<Transform>();
			{
				tf->SetScale(Vector3(obstacleWidth, obstacleHeight, 1.f));
				tf->SetPosition(Vector3(400.f, -(Global::ClientOption.height - (obstacleHeight)) / 2, 0.f));
			}
			btmObstacle->AddComponent<BoxCollider2D>();
			btmObstacle->AddComponent<Obstacle>();

			auto cloud = Instantiate();
			{
				auto cloudTf = cloud->AddComponent<Transform>();
				{
					cloudTf->SetParent(tf);
					cloudTf->SetScale(Vector3(100.f, 75.f, 1.f));
					cloudTf->SetLocalPosition(Vector3(0.f, 0.5f, 0.f));
				}
				auto sr = cloud->AddComponent<SpriteRenderer>();
				{
					sr->SetTexture(ASSET.Get<Texture>(L"Texture_Cloud"));
					sr->OrderInLayer = 15;
				}
				cloud->AddComponent<BoxCollider2D>();
			}
		}
	}
}

