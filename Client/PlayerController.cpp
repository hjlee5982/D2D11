#include "pch.h"
#include "PlayerController.h"
#include "SpriteRenderer.h"
#include "AssetManager.h"
#include "Texture.h"
#include <variant>

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

		f32 gravity = -9.81f * 300.f;

		_velocity += gravity * TIMER.DeltaTime();

		pos += up * _velocity * TIMER.DeltaTime();

		Owner()->transform->SetPosition(pos);
	}
}

void PlayerController::OnCollisionEnter(sptr<BoxCollider2D> collider)
{

}

void PlayerController::Jump()
{
	if (_trigger == false)
	{
		_trigger = true;
	}

	_velocity = 600.f;
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
