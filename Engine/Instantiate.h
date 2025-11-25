#pragma once

#include "GameObjectManager.h"
#include "UIBoundary.h"

template<typename... Args>
static sptr<GameObject> Instantiate(EObjectType type = EObjectType::GameObject, Args&&... args)
{
	sptr<GameObject> go = makeSptr<GameObject>();

	go->transform = go->AddComponent<Transform>(std::forward<Args>(args)...);

	switch (type)
	{
	case EObjectType::GameObject:

		GAMEOBJECT.AddGameObject(go);

		break;

	case EObjectType::UI:

		go->AddComponent<UIBoundary>();

		GAMEOBJECT.AddUIObject(go);

		break;
	}

	return go;
}