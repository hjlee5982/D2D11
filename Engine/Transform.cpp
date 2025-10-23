#include "pch.h"
#include "Transform.h"

void Transform::SetOwner(sptr<class GameObject> owner)
{
	gameObject = owner;
}
