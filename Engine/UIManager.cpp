#include "pch.h"
#include "UIManager.h"
#include "Camera.h"

void UIManager::Awake()
{
	_uiCamera = makeSptr<Camera>();
	{
		CameraDesc desc;
		{
			desc.Type = ProjectionType::OrthoUI;
		}
		_uiCamera->Initialize(desc);
	}
}


void UIManager::Update()
{
	_uiCamera->Update();
}

void UIManager::AddUIObject(sptr<class UIObject> ui)
{
	_uiObjects.push_back(ui);
}