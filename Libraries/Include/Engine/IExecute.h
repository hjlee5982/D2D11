#pragma once

class IExecute abstract
{
public:
	virtual void Awake()	  abstract;
	virtual void Start()	  abstract;
	virtual void Update()	  abstract;
	virtual void LateUpdate() abstract;
};

