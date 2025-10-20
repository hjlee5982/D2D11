#include "pch.h"
#include "GameObject.h"

GameObject::GameObject()
{
    AddComponent<Transform>();
}

sptr<Component> GameObject::GetComponent()
{
    return sptr<Component>();
}
