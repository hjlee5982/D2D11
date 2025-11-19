#pragma once

class UIObject abstract : public Object
{
public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
public:
	void SetActive(bool active);
private:
	Dictionary<u64, sptr<class Component>> _components;
public:
	sptr<class RectTransform> rectTransform;
};


