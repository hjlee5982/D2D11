#pragma once

class Transform : public Component
{
public:
	virtual ~Transform() = default;
public:
	virtual void Awake()      override;
	virtual void Start()	  override;
	virtual void Update()     override;
	virtual void LateUpdate() override;
public:
	Matrix GetWorldMatrix()
	{
		return _worldMatrix;
	}
public:
	Vector3 GetPosition()
	{
		return _position;
	}
	Vector3 GetScale()
	{
		return _scale;
	}
	Quaternion GetRotation()
	{
		return _rotation;
	}
public:
	void SetPosition(const Vector3& position);
	void SetScale   (const Vector3& scale);
	void SetRotation(const Quaternion& rotation);
public:
	void Translation(const Vector3& dir, float speed);
private:
	Matrix _worldMatrix = Matrix::Identity;
private:
	Vector3    _position = Vector3::Zero;
	Vector3    _scale    = Vector3::One;
	Quaternion _rotation = Quaternion::Identity;
private:
	Vector3 _right = Vector3(1.f, 0.f, 0.f);
	Vector3 _up    = Vector3(0.f, 1.f, 0.f);
	Vector3 _look  = Vector3(0.f, 0.f, 1.f);
};