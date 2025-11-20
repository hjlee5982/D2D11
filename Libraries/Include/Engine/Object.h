#pragma once

class Object abstract : public IJson
{
public:
	string name   = "none";
	string tag    = "none";
	bool isActive = true;
};

#include "GameObject.h"
#include "UIObject.h"
#include "GameObjectManager.h"
#include "UIManager.h"

template<typename T, typename... Args>
static sptr<T> Instantiate(Args&&... args)
{
	if constexpr (std::is_same_v<T, GameObject>)
	{
		sptr<T> go = makeSptr<T>();

		go->transform = go->AddComponent<Transform>(std::forward<Args>(args)...);

		GAMEOBJECT.AddGameObject(go);

		return go;
	}
	else if (std::is_same_v<T, UIObject>)
	{
		sptr<T> ui = makeSptr<T>();

		ui->rectTransform = ui->AddComponent<RectTransform>(std::forward<Args>(args)...);

		UI.AddUIObject(ui);

		return ui;
	}

	return nullptr;
}