#include "pch.h"
#include "GameObject.h"

void GameObject::Awake()
{
	for (auto& com : _components)
	{
		com.second->Awake();
	}
}

void GameObject::Start()
{
	for (auto& com : _components)
	{
		com.second->Start();
	}
}

void GameObject::Update()
{
	for (auto& com : _components)
	{
		com.second->Update();
	}
}

void GameObject::LateUpdate()
{
	for (auto& com : _components)
	{
		com.second->LateUpdate();
	}
}
