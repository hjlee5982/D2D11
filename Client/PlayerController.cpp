#include "pch.h"
#include "PlayerController.h"
#include "SpriteRenderer.h"
#include "AssetManager.h"
#include "Texture.h"
#include <variant>

BOOL WINAPI ConsoleHandler(DWORD signal)
{
	if (signal == CTRL_CLOSE_EVENT)
	{
		FreeConsole();
		std::cout.clear();
		return TRUE;
	}
	return FALSE;
}

void PlayerController::Start()
{
	_sr = GetComponent<SpriteRenderer>();

	//INPUT.FindAction("Jump")->performed = [this]() { Jump(); };
	INPUT.FindAction("Jump")->started = std::bind(&PlayerController::Jump, this);
	INPUT.FindAction("Console")->started = std::bind(&PlayerController::ToggleConsole, this);
}

void PlayerController::ToggleConsole()
{
	if (_isConsoleOpen == false)
	{
		OpenConsole();
		_isConsoleOpen = true;
	}
	else
	{
		CloseConsole();
		_isConsoleOpen = false;
	}
}

void PlayerController::OpenConsole()
{
	if (AllocConsole())
	{
		// 표준 입출력 재연결
		FILE* fp;
		freopen_s(&fp, "CONOUT$", "w", stdout);
		freopen_s(&fp, "CONIN$", "r", stdin);
		SetConsoleCtrlHandler(ConsoleHandler, TRUE);

		std::cout << "Console opened. Type 'exit' to close.\n";
	}
}

void PlayerController::CloseConsole()
{
	FreeConsole();
	std::cout.clear();
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
