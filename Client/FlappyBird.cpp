#include "pch.h"
#include "FlappyBird.h"
#include "GameObject.h"
#include "Camera.h"
#include "BackgroundController.h"

void FlappyBird::InitializeScene()
{
	// 유니티 Scene에 물체 배치하듯이 코드로 배치하면 됨
	// 카메라는 엔진에서 기본 생성해줌

	// 빈 게임오브젝트 추가(트랜스폼은 자동으로 추가해줌)
	auto bg1 = Instantiate();
	{
		// 컴포넌트 추가
		bg1->AddComponent<SpriteRenderer>();
		bg1->AddComponent<BoxCollider2D>();

		// 스크립트 컴포넌트 추가
		auto bc = bg1->AddComponent<BackgroundController>();
		{
			// 스크립트에 변수 뚫어놓고 수정하듯이 수정하면 됨
			bc->_scale = Vector3(150.f, 150.f, 1.f);
			bc->_position = Vector3(-100.f, 50.f, 0.f);
		}
	}
	auto bg2 = Instantiate();
	{
		bg2->AddComponent<SpriteRenderer>();
		bg2->AddComponent<BoxCollider2D>();

		bg2->transform->SetScale(Vector3(150.f, 150.f, 1.f));
		bg2->transform->SetPosition(Vector3(100.f, 0.f, 0.f));
		/*auto bc = bg2->AddComponent<BackgroundController>();
		{
			bc->_scale = Vector3(150.f, 150.f, 1.f);
			bc->_position = Vector3(100.f, 0.f, 0.f);
		}*/
	}
}