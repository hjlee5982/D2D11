#include "pch.h"
#include "ObstacleGenerator.h"
#include "Obstacle.h"
#include "BoxCollider2D.h"
#include "AssetManager.h"
#include "SpriteRenderer.h"
#include "Texture.h"
#include "Transform.h"

void ObstacleGenerator::Start()
{
	for (int i = 0; i < _poolSize; ++i)
	{
		auto obstacle = Instantiate();
		{
			{
				obstacle->tag = "Obstacle";
			}
			auto tf = obstacle->AddComponent<Transform>();
			auto sr = obstacle->AddComponent<SpriteRenderer>();
			{
				sr->SetTexture(ASSET.Get<Texture>(L"Texture_Rope"));
			}
			auto bc = obstacle->AddComponent<BoxCollider2D>();
			{
				bc->SetLocalScale(Vector3(0.5f, 1.f, 1.f));
			}
			auto ot = obstacle->AddComponent<Obstacle>();
			{
				ot->SetGenerator(shared_from_this());
			}

			auto cloud = Instantiate();
			{
				{
					cloud->name = "Cloud";
				}
				auto cloudTf = cloud->AddComponent<Transform>();
				{
					cloudTf->SetParent(tf);
					cloudTf->SetScale(Vector3(1.f, 0.5f, 1.f));
					cloudTf->SetLocalPosition(Vector3(0.f, -0.5f, 0.f));
				}
				auto sr = cloud->AddComponent<SpriteRenderer>();
				{
					sr->SetTexture(ASSET.Get<Texture>(L"Texture_Cloud"));
					sr->OrderInLayer = 15;
				}
				auto bc = cloud->AddComponent<BoxCollider2D>();
				{
					bc->SetLocalScale(Vector3(0.8f, 0.8f, 1.f));
				}
			}
		}
		obstacle->SetActive(false);

		_obstacles.push(obstacle);
	}
}

void ObstacleGenerator::Update()
{
	Generate();
}

void ObstacleGenerator::ReturnPool(sptr<class GameObject> obstacle)
{
	_obstacles.push(obstacle);
	obstacle->SetActive(false);
}

void ObstacleGenerator::Generate()
{
	_elapsed += TIMER.DeltaTime();

	if (_elapsed >= _frequency)
	{
		_elapsed = 0.f;

		f32 height = RANDOM.Range(-2.f, 2.f);
		f32 gap    = RANDOM.Range(3.3f, 3.7f);

		auto top = _obstacles.front(); _obstacles.pop();
		top->SetActive(true);
		{
			auto tf = top->GetComponent<Transform>();
			{
				tf->SetScale(Vector3(1.f, gap + height, 1.f));

				f32 y = tf->GetScale().y;
				tf->SetPosition(Vector3(5.f, 5.f - y / 2.f, 0.f));
			}
			auto ctf = tf->GetChild(0)->GetComponent<Transform>();
			{
				ctf->SetParent(tf);
				ctf->SetScale(Vector3(1.2f, 0.8f, 1.f));
				ctf->SetLocalPosition(Vector3(0.f, -0.5f, 0.f));
			}
		}
		auto btm = _obstacles.front(); _obstacles.pop();
		btm->SetActive(true);
		{
			auto tf = btm->GetComponent<Transform>();
			{
				tf->SetScale(Vector3(1.f, gap - height, 1.f));

				f32 y = tf->GetScale().y;
				tf->SetPosition(Vector3(5.f, -5.f + y / 2.f, 0.f));
			}
			auto ctf = tf->GetChild(0)->GetComponent<Transform>();
			{
				ctf->SetParent(tf);
				ctf->SetScale(Vector3(1.2f, 0.8f, 1.f));
				ctf->SetLocalPosition(Vector3(0.f, 0.5f, 0.f));
			}
		}
	}
}

