#include "pch.h"
#include "FlappyBird.h"
#include "GameObject.h"
#include "Camera.h"

void FlappyBird::Awake()
{
}

void FlappyBird::Start()
{
	int a = 0;

	// ī�޶�
	{
		_camera = Instantiate();
		{
			auto camera = _camera->AddComponent<Camera>();
			{
				camera->SetCameraOption(0.1f, 300.f, 60.f);
			}
		}
	}
	// ���
	{
		_bg = Instantiate();
		{
			_bg->AddComponent<SpriteRenderer>();

			_bg->transform->worldMatrix._43 = 2.0f;
		}
	}
}

void FlappyBird::Update()
{
	auto camera = _camera->GetComponent<Camera>();
	camera->Update();
}

void FlappyBird::LateUpdate()
{
}
