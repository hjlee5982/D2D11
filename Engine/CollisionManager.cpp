#include "pch.h"
#include "CollisionManager.h"
#include "BoxCollider2D.h"

void CollisionManager::Awake()
{
}

void CollisionManager::Update()
{
	for (auto& co1 : _colliders)
	{
		for (auto& co2 : _colliders)
		{
			if (co1 == co2)
			{
				continue;
			}
			else
			{

			}
		}
	}
}

void CollisionManager::AddCollider(sptr<BoxCollider2D> collider)
{
	_colliders.push_back(collider);
}
