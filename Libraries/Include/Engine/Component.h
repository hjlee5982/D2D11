#pragma once

class Component abstract : public Object
{
public:
	virtual ~Component() = default;
public:
	virtual void SetOwner(sptr<class GameObject> owner) = 0;
public:
	sptr<class GameObject> gameObject;
};

