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

void MainScene::Awake()
{
	// 리소스 로드
	LoadResources();

	// 인풋 설정
	SetInputSystem();

	// 오브젝트 배치
	AddGameObject();
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
	auto camera = CreateGameObject();
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
	auto bg1 = CreateGameObject();
	{
		{
			bg1->name = "Background_1";
		}
		auto tf = bg1->AddComponent<Transform>();
		{
			tf->SetScale(Vector3(1420.f, 800.f, 0.f));
			tf->SetPosition(Vector3(-710.f, 0.f, 0.f));
		}
		auto sr = bg1->AddComponent<SpriteRenderer>();
		{
			sr->SetTexture(ASSET.Get<Texture>(L"Texture_BackGround"));
			sr->OrderInLayer = 0;
		}
		auto bc = bg1->AddComponent<BackgroundController>();
	}
	auto bg2 = CreateGameObject();
	{
		{
			bg2->name = "Background_2";
		}
		auto tf = bg2->AddComponent<Transform>();
		{
			tf->SetScale(Vector3(1420.f, 800.f, 0.f));
			tf->SetPosition(Vector3(710.f, 0.f, 0.f));
		}
		auto sr = bg2->AddComponent<SpriteRenderer>();
		{
			sr->SetTexture(ASSET.Get<Texture>(L"Texture_BackGround"));
			sr->OrderInLayer = 0;
		}
		bg2->AddComponent<BackgroundController>();
	}
	// 플레이어
	auto player = CreateGameObject();
	{
		{
			player->name = "Player";
			player->tag  = "Player";
		}
		auto tf = player->AddComponent<Transform>();
		{
			tf->SetScale(Vector3(200.f, 200.f, 0.f));
			tf->SetPosition(Vector3(-150.f, 100.f, 0.f));
		}
		auto sr = player->AddComponent<SpriteRenderer>();
		{
			sr->SetTexture(ASSET.Get<Texture>(L"Texture_Player_1"));
			sr->OrderInLayer = 10;
		}
		auto bc = player->AddComponent<BoxCollider2D>();
		{
			bc->SetScale(Vector3(0.35f, 0.35f, 0.35f));
			bc->SetPosition(Vector3(0.02f, 0.f, 0.f));
		}
		player->AddComponent<PlayerController>();
	}
	// 바운더리(천장)
	auto topBoundary = CreateGameObject();
	{
		{
			topBoundary->name = "TopBoundary";
			topBoundary->tag  = "Obstacle";
		}
		auto tf = topBoundary->AddComponent<Transform>();
		{
			tf->SetScale(Vector3(Global::ClientOption.width, 1.f, 0.f));
			tf->SetPosition(Vector3(0.f, Global::ClientOption.height / 2, 0.f));
		}
		topBoundary->AddComponent<BoxCollider2D>();
	}
	// 바운더리(바닥)
	auto btmBoundary = CreateGameObject();
	{
		{
			btmBoundary->name = "BtmBoundary";
			btmBoundary->tag  = "Obstacle";
		}
		auto tf = btmBoundary->AddComponent<Transform>();
		{
			tf->SetScale(Vector3(Global::ClientOption.width, 1.f, 0.f));
			tf->SetPosition(Vector3(0.f, -Global::ClientOption.height / 2, 0.f));
		}
		btmBoundary->AddComponent<BoxCollider2D>();
	}
	// 장애물 생성기
	auto oj = CreateGameObject();
	{
		oj->AddComponent<ObstacleGenerator>();
	}
}
