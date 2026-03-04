#pragma once

#include "GameObjectManager.h"
#include "SceneManager.h"
#include "Transform.h"

template<typename... Args>
static sptr<GameObject> Instantiate(Args&&... args)
{
	sptr<GameObject> go = makeSptr<GameObject>();

	go->transform = go->AddComponent<Transform>(std::forward<Args>(args)...);

	GAMEOBJECT.AddGameObject(go);

	return go;
}