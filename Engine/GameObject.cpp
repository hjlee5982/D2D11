#include "pch.h"
#include "GameObject.h"
#include "Component.h"

void GameObject::MakeJson()
{
	for (auto& com : _components)
	{
		_json["name"] = name;

		com.second->MakeJson();

		nlohmann::json comJson;
		comJson["type"] = com.second->GetTypeName();
		comJson["data"] = com.second->_json;

		_json["Components"].push_back(comJson);
	}
}

void GameObject::LoadJson(const nlohmann::json& json)
{
	for (auto& com : _components)
	{
		com.second->LoadJson(json);
	}
}

void GameObject::AddComponent(sptr<class Component> com)
{
	com->SetOwner(shared_from_this());
	com->Init();

	if (com->GetType() == typeid(Transform).hash_code())
	{
		transform = std::static_pointer_cast<Transform>(com);
	}
	_components.emplace(com->GetType(), com);
}

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

void GameObject::FixedUpdate()
{
	for (auto& com : _components)
	{
		com.second->FixedUpdate();
	}
}

void GameObject::OnCollisionEnter2D(sptr<BoxCollider2D> collider)
{
	for (auto& com : _components)
	{
		com.second->OnCollisionEnter2D(collider);
	}
}