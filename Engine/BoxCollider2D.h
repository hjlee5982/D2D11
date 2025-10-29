#pragma once

class BoxCollider2D : public Component
{
public:
	virtual void Awake()      override;
	virtual void Start()      override;
	virtual void Update()     override;
	virtual void LateUpdate() override;
};

