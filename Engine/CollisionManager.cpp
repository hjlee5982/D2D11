#include "pch.h"
#include "CollisionManager.h"
#include "BoxCollider2D.h"
#include "GameObject.h"

void CollisionManager::Awake()
{
}

void CollisionManager::FixedUpate()
{
	for (auto co1 : _colliders)
	{
		for (auto& co2 : _colliders)
		{
			auto co1_lock = co1.lock();
			auto co2_lock = co2.lock();

			// 같은 콜라이더는 패스
			if (co1_lock == co2_lock)
			{
				continue;
			}
			// 둘 중 하나라도 비활성화라면 패스
			else if (co1_lock->Owner()->isActive == false || co2_lock->Owner()->isActive == false)
			{
				continue;
			}
			else
			{
				AABB lhs = std::static_pointer_cast<BoxCollider2D>(co1.lock())->GetAABB();
				AABB rhs = std::static_pointer_cast<BoxCollider2D>(co2.lock())->GetAABB();

				if (max(lhs.min.x, rhs.min.x) < min(lhs.max.x, rhs.max.x) &&
					max(lhs.min.y, rhs.min.y) < min(lhs.max.y, rhs.max.y))
				{
					co1.lock()->Owner()->OnCollisionEnter2D(std::static_pointer_cast<BoxCollider2D>(co2.lock()));
					co2.lock()->Owner()->OnCollisionEnter2D(std::static_pointer_cast<BoxCollider2D>(co1.lock()));
				}
			}
		}
	}
}

void CollisionManager::AddCollider(sptr<Component> collider)
{
	_colliders.push_back(collider);
}

