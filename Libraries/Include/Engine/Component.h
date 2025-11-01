#pragma once

class Component abstract : public Object
{
public:
	virtual ~Component() = default;
public:
	virtual void SetOwner(sptr<class GameObject> owner);
public:
	virtual void Awake()     {}
	virtual void Start()     {}
	virtual void Update()    {}
	virtual void LateUpdate(){}
protected:
	template<typename T>
	sptr<T> GetComponent()
	{
		return gameObject.lock()->GetComponent<T>();
	}
public:
	sptr<GameObject> Owner()
	{
		return gameObject.lock();
	}
public:
	// GameObject가 Component를 소유하고 있으니
	// Component는 GameObject를 소유하면 안됨. 순환참조됨
	// sptr<GameObject> gameObject;
	wptr<GameObject> gameObject;
};

