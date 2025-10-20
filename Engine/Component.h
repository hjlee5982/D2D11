#pragma once

class Component abstract : public Object
{
public:
	virtual ~Component() = default;
public:
	void SetOwner(sptr<class GameObject> _owner);
private:
	sptr<class GameObject> owner;
};

