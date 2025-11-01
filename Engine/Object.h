#pragma once

class Object abstract : public IJson
{
public:
	virtual ~Object() = default;
public:
	virtual void OnCollisionEnter(sptr<class BoxCollider2D> collider) {};
public:
	const string& GetName();
protected:
	string _name;
};

