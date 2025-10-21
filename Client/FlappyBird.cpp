#include "pch.h"
#include "FlappyBird.h"

void FlappyBird::Awake()
{
	int a = 0;
}

void FlappyBird::Start()
{
	int a = 0;

	sptr<GameObject> go = makeSptr<GameObject>();
	{
		sptr<SpriteRenderer> renderer = go->AddComponent<SpriteRenderer>();
		{
			// renderer->sprite = sprite
		}
	}
}

void FlappyBird::Update()
{
	int a = 0;
}

void FlappyBird::LateUpdate()
{
	int a = 0;
}
