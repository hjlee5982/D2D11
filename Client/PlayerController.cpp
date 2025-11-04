#include "pch.h"
#include "PlayerController.h"
#include "SpriteRenderer.h"
#include "AssetManager.h"
#include "Texture.h"

void PlayerController::Start()
{
	_sr = GetComponent<SpriteRenderer>();
}

void PlayerController::Update()
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

void PlayerController::OnCollisionEnter(sptr<BoxCollider2D> collider)
{
}
