#pragma once

#include "SceneManager.h"
#include "GameObject.h"
#include "Transform.h"

template<typename... Args>
static sptr<GameObject> Instantiate(Args&&... args)
{
	sptr<GameObject> go = makeSptr<GameObject>();

	go->transform = go->AddComponent<Transform>(std::forward<Args>(args)...);

	SCENE.AddGameObject(go);

	return go;
}

static void Destroy(sptr<GameObject> go)
{
	SCENE.Destroy(go);
}