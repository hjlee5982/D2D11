#pragma once

class Object abstract : public IJson
{
public:
	virtual const uint64_t  GetType() const { return 0; };
	virtual const char* GetTypeName() const { return nullptr; };
public:
	virtual void OnCollisionEnter2D(sptr<class BoxCollider2D> collider) {};
public:
	const string& GetName();
public:
	string name;
};

