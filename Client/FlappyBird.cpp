#include "pch.h"
#include "FlappyBird.h"
#include "GameObject.h"
#include "Camera.h"
#include "BackgroundController.h"
#include "PlayerController.h"
#include "SpriteRenderer.h"

void FlappyBird::InitializeScene()
{
	// 배경화면
	auto bg1 = Instantiate();
	{
		auto tf = bg1->AddComponent<Transform>();
		{
			tf->SetScale(Vector3(1420.f, 800.f, 0.f));
			tf->SetPosition(Vector3(-710.f, 0.f, 0.f));
		}
		auto sr = bg1->AddComponent<SpriteRenderer>();
		{
			sr->OrderInLayer = 0;
		}
		auto bc = bg1->AddComponent<BackgroundController>();
	}
	auto bg2 = Instantiate();
	{
		auto tf = bg2->AddComponent<Transform>();
		{
			tf->SetScale(Vector3(1420.f, 800.f, 0.f));
			tf->SetPosition(Vector3(710.f, 0.f, 0.f));
		}
		auto sr = bg2->AddComponent<SpriteRenderer>();
		{
			sr->OrderInLayer = 0;
		}
		bg2->AddComponent<BackgroundController>();
	}
	// 플레이어
	auto player = Instantiate();
	{
		auto tf = player->AddComponent<Transform>();
		{
			tf->SetScale(Vector3(100.f, 100.f, 0.f));
			tf->SetPosition(Vector3(50.f, 50.f, 0.f));
		}
		auto sr = player->AddComponent<SpriteRenderer>();
		{
			sr->OrderInLayer = 10;
		}
		player->AddComponent<BoxCollider2D>();
		player->AddComponent<PlayerController>();
	}
	

	IngredientInfo info;
	{
		info.calories = 5;
		info.carbohydrate = 10.f;
		info.protein = 15.f;
		info.fat = 20.f;
	}

	Product pd;
	{
		pd.code = 251101;
		pd.tag = "Pizza";

		pd.ingredient = info;

		pd.productData["production_data"] = "2025-11-01";
		pd.productData["expiry_data"] = "2026-11-01";
	}

	pd.MakeJson();
	nlohmann::json json = pd._json;

	std::ofstream file("Test.json");
	file << json.dump(4);
}
