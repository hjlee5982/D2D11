#include "pch.h"
#include "PlayerController.h"
#include "SpriteRenderer.h"
#include "AssetManager.h"
#include "Texture.h"
#include <variant>
#include "InputSystem.h"
#include "GameObject.h"
#include "Transform.h"
#include "BoxCollider2D.h"
#include "Event.h"
#include "EventManager.h"
#include "Obstacle.h"

void PlayerController::Start()
{
	_sr = GetComponent<SpriteRenderer>();

	//INPUT.FindAction("Jump")->performed = [this]() { Jump(); };
	INPUT.FindAction("Jump")->started = std::bind(&PlayerController::Jump, this);

	
}

void PlayerController::Update()
{
	TempAnimation();

	if (_trigger == true)
	{
		Vector3	pos = Owner()->transform->GetPosition();
		Vector3 up = Owner()->transform->GetUp();

		up.Normalize();

		f32 gravity = -9.81f * 4.f;

		_velocity += gravity * TIMER.DeltaTime();

		pos += up * _velocity * TIMER.DeltaTime();

		Owner()->transform->SetPosition(pos);
	}
}

void PlayerController::OnCollisionEnter2D(sptr<BoxCollider2D> collider)
{
	if (collider->Owner()->tag == "Obstacle")
	{
		auto obstacle = collider->Owner()->GetComponent<Obstacle>();

		// 장애물 충돌
		if (obstacle != nullptr && obstacle->_isColliding == false)
		{
			LOG_INFO("충돌함");
			EVENT::SendEvent(AddScoreEvent{});

			obstacle->_isColliding = true;
		}
	}
}

void PlayerController::Jump()
{
	if (_trigger == false)
	{
		_trigger = true;
	}

	_velocity = 8.f;
	_index = 5;
}

void PlayerController::TempAnimation()
{
	_elapsed += TIMER.DeltaTime();

	if (_elapsed >= 0.05f)
	{
		auto texture = ASSET.Get<Texture>(L"Texture_Player_" + std::to_wstring(_index));

		_sr->SetTexture(texture);

		_elapsed = 0.f;

		++_index;

		if (_index > 10)
		{
			_index = 1;
		}
	}
}
