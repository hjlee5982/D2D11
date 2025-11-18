#include "pch.h"
#include "MainScene.h"
#include "GameObject.h"
#include "Camera.h"
#include "BackgroundController.h"
#include "PlayerController.h"
#include "SpriteRenderer.h"
#include "Texture.h"
#include "AssetManager.h"
#include "ObstacleGenerator.h"
#include "Renderer.h"

void MainScene::Awake()
{
	// 리소스 로드
	LoadResources();

	//// 인풋 설정
	SetInputSystem();

	//// 오브젝트 배치
	AddGameObject();

	//// 엔진 설정
	EngineSetting();
}

void MainScene::LoadResources()
{
	// 배경화면
	{
		sptr<Texture> texture = makeSptr<Texture>();
		texture->CreateTexture(L"../Assets/Image/BackGround.png");
		ASSET.Add(L"Texture_BackGround", texture);
	}
	// 플레이어
	{
		for (int i = 1; i <= 10; ++i)
		{
			sptr<Texture> texture = makeSptr<Texture>();
			texture->CreateTexture(L"../Assets/Image/Player/Player_" + std::to_wstring(i) + L".png");
			ASSET.Add(L"Texture_Player_" + std::to_wstring(i), texture);
		}
	}
	// 장애물(구름)
	{
		sptr<Texture> texture = makeSptr<Texture>();
		texture->CreateTexture(L"../Assets/Image/Cloud.png");
		ASSET.Add(L"Texture_Cloud", texture);
	}
	// 장애물(밧줄)
	{
		sptr<Texture> texture = makeSptr<Texture>();
		texture->CreateTexture(L"../Assets/Image/Rope.png");
		ASSET.Add(L"Texture_Rope", texture);
	}
}

void MainScene::SetInputSystem()
{
	InputMap map;
	{
		map.AddAction("Jump", { 'E', VK_SPACE});
	}
	INPUT.AddMap(map);
}

void MainScene::AddGameObject()
{
	// 카메라
	auto camera = Instantiate();
	{
		{
			camera->name = "MainCamera";
		}
		{
			auto tf = camera->AddComponent<Transform>();
			auto cm = camera->AddComponent<Camera>();
		}
	}
	// 배경화면 

	f32 bgWidth = 2200.f;

	auto bg1 = Instantiate();
	{
		{
			bg1->name = "Background_1";
		}
		auto tf = bg1->AddComponent<Transform>();
		{
			tf->SetScale(Vector3(bgWidth, 1000.f, 1.f));
			tf->SetPosition(Vector3(0.f, 0.f, 0.f));
		}
		auto sr = bg1->AddComponent<SpriteRenderer>();
		{
			sr->SetTexture(ASSET.Get<Texture>(L"Texture_BackGround"));
			sr->OrderInLayer = 0;
		}
		auto bc = bg1->AddComponent<BackgroundController>();
	}
	auto bg2 = Instantiate();
	{
		{
			bg2->name = "Background_2";
		}
		auto tf = bg2->AddComponent<Transform>();
		{
			tf->SetScale(Vector3(bgWidth, 1000.f, 1.f));
			tf->SetPosition(Vector3(bgWidth, 0.f, 0.f));
		}
		auto sr = bg2->AddComponent<SpriteRenderer>();
		{
			sr->SetTexture(ASSET.Get<Texture>(L"Texture_BackGround"));
			sr->OrderInLayer = 0;
		}
		bg2->AddComponent<BackgroundController>();
	}
	// 플레이어
	auto player = Instantiate();
	{
		{
			player->name = "Player";
			player->tag  = "Player";
		}
		auto tf = player->AddComponent<Transform>();
		{
			tf->SetScale(Vector3(200.f, 200.f, 1.f));
			tf->SetPosition(Vector3(-150.f, 100.f, 0.f));
		}
		auto sr = player->AddComponent<SpriteRenderer>();
		{
			sr->SetTexture(ASSET.Get<Texture>(L"Texture_Player_1"));
			sr->OrderInLayer = 30;
		}
		auto bc = player->AddComponent<BoxCollider2D>();
		{
			bc->SetLocalScale(Vector3(0.35f, 0.35f, 0.35f));
			bc->SetLocalPosition(Vector3(0.02f, 0.f, 0.f));
		}
		player->AddComponent<PlayerController>();
	}
	// 바운더리(천장)
	auto topBoundary = Instantiate();
	{
		{
			topBoundary->name = "TopBoundary";
			topBoundary->tag  = "Obstacle";
		}
		auto tf = topBoundary->AddComponent<Transform>();
		{
			tf->SetLocalScale(Vector3(Global::ClientOption.width, 1.f, 1.f));
			tf->SetLocalPosition(Vector3(0.f, Global::ClientOption.height / 2, 0.f));
		}
		topBoundary->AddComponent<BoxCollider2D>();
	}
	// 바운더리(바닥)
	auto btmBoundary = Instantiate();
	{
		{
			btmBoundary->name = "BtmBoundary";
			btmBoundary->tag  = "Obstacle";
		}
		auto tf = btmBoundary->AddComponent<Transform>();
		{
			tf->SetLocalScale(Vector3(Global::ClientOption.width, 1.f, 1.f));
			tf->SetLocalPosition(Vector3(0.f, -Global::ClientOption.height / 2, 0.f));
		}
		btmBoundary->AddComponent<BoxCollider2D>();
	}
	// 장애물 생성기
	auto oj = Instantiate();
	{
		oj->AddComponent<ObstacleGenerator>();
	}
}

void MainScene::EngineSetting()
{
	RENDERER.colliderRendering = true;
}
