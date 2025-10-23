#pragma once

class Transform : public Component
{
public:
	virtual ~Transform() = default;
public:
	virtual void SetOwner(sptr<class GameObject> owner) override;
public:
	Matrix  worldMatrix = Matrix::Identity;
public:
	Vector3    position = Vector3::Zero;
	Quaternion rotation = Quaternion::Identity;
};

