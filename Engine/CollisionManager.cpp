#include "pch.h"
#include "CollisionManager.h"
#include "BoxCollider2D.h"

void CollisionManager::Awake()
{
}

void CollisionManager::FixedUpate()
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
				AABB lhs = co1->GetAABB();
				AABB rhs = co2->GetAABB();

				if (max(lhs.min.x, rhs.min.x) < min(lhs.max.x, rhs.max.x) &&
					max(lhs.min.y, rhs.min.y) < min(lhs.max.y, rhs.max.y))
				{
					co1->Owner()->OnCollisionEnter(co2);
					co2->Owner()->OnCollisionEnter(co1);
				}
			}
		}
	}
}

void CollisionManager::AddCollider(sptr<BoxCollider2D> collider)
{
	_colliders.push_back(collider);
}

