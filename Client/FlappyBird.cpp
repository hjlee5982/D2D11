#include "pch.h"
#include "FlappyBird.h"
#include "GameObject.h"
#include "Camera.h"
#include "BackgroundController.h"
#include "PlayerController.h"

void FlappyBird::InitializeScene()
{
	// 배경화면
	auto bg1 = Instantiate();
	{
		bg1->AddComponent<SpriteRenderer>();
		bg1->AddComponent<BackgroundController>();

		bg1->transform->SetScale(Vector3(1420.f, 800.f, 1.f));
		bg1->transform->SetPosition(Vector3(-710.f, 0.f, 0.f));
	}
	auto bg2 = Instantiate();
	{
		bg2->AddComponent<SpriteRenderer>();
		bg2->AddComponent<BackgroundController>();

		bg2->transform->SetScale(Vector3(1420.f, 800.f, 1.f));
		bg2->transform->SetPosition(Vector3(710.f, 0.f, 0.f));
	}
	// 플레이어
	/*auto player = Instantiate();
	{
		player->AddComponent<SpriteRenderer>();
		player->AddComponent<BoxCollider2D>();
		player->AddComponent<PlayerController>();
	}*/

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
