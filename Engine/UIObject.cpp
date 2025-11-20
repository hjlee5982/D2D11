#include "pch.h"
#include "UIObject.h"

void UIObject::Awake()
{
}

void UIObject::Start()
{
}

void UIObject::Update()
{
}

void UIObject::LateUpdate()
{
}

void UIObject::FixedUpdate()
{
}

void UIObject::SetActive(bool active)
{
	isActive = active;

	rectTransform->SetActive(active);
}
