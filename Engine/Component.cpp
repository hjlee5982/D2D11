#include "pch.h"
#include "Component.h"

void Component::SetOwner(sptr<GameObject> _owner)
{
	owner = _owner;
}
