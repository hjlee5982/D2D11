#pragma once

class Component abstract : public Object
{
public:
	virtual ~Component() = default;
public:
	virtual void SetOwner(sptr<class GameObject> owner);
public:
	virtual void Awake()      = 0;
	virtual void Start()      = 0;
	virtual void Update()     = 0;
	virtual void LateUpdate() = 0;
protected:
	template<typename T>
	sptr<T> GetComponent()
	{
		return gameObject->GetComponent<T>();
	}
public:
	sptr<GameObject> gameObject;
};

