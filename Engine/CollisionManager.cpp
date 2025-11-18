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
			if (co1.lock() == co2.lock())
			{
				continue;
			}
			else
			{
				AABB lhs = co1.lock()->GetAABB();
				AABB rhs = co2.lock()->GetAABB();

				if (max(lhs.min.x, rhs.min.x) < min(lhs.max.x, rhs.max.x) &&
					max(lhs.min.y, rhs.min.y) < min(lhs.max.y, rhs.max.y))
				{
					co1.lock()->Owner()->OnCollisionEnter2D(co2.lock());
					co2.lock()->Owner()->OnCollisionEnter2D(co1.lock());
				}
			}
		}
	}
}

void CollisionManager::AddCollider(sptr<BoxCollider2D> collider)
{
	_colliders.push_back(collider);
}

