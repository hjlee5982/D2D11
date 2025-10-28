#include "pch.h"
#include "FlappyBird.h"
#include "GameObject.h"
#include "Camera.h"
#include "BackgroundController.h"

void FlappyBird::InitializeScene()
{
	// 카메라
	{
		_camera = Instantiate();
		{
			// auto cm = _camera->AddComponent<Camera>();

			// cm->gameObject->transform->SetPosition(Vector3(0.f, 0.f, -10.f));
		}
	}
	//// 배경
	//{
	//	_bgL = Instantiate();
	//	{
	//		_bgL->AddComponent<SpriteRenderer>();

	//		auto bc = _bgL->AddComponent<BackgroundController>();
	//		{
	//			bc->_scale    = Vector3(1600.f, 800.f, 1.f);
	//			bc->_position = Vector3(-800.f, 0.f, 0.f);
	//		}
	//	}
	//	_bgR = Instantiate();
	//	{
	//		_bgR->AddComponent<SpriteRenderer>();

	//		auto bc = _bgR->AddComponent<BackgroundController>();
	//		{
	//			bc->_scale    = Vector3(1600.f, 800.f, 1.f);
	//			bc->_position = Vector3(800.f, 0.f, 0.f);
	//		}
	//	}
	//}
}