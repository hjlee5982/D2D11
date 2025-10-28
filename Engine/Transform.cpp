#include "pch.h"
#include "Transform.h"

void Transform::Awake()
{
}

void Transform::Start()
{
}

void Transform::Update()
{
	Matrix scale    = Matrix::CreateScale(_scale);
	Matrix rotation = Matrix::CreateFromQuaternion(_rotation);
	Matrix position = Matrix::CreateTranslation(_position);

	_worldMatrix = scale * rotation * position;

	_right = Vector3(_worldMatrix._11, _worldMatrix._12, _worldMatrix._13);
	_up    = Vector3(_worldMatrix._21, _worldMatrix._22, _worldMatrix._23);
	_look  = Vector3(_worldMatrix._31, _worldMatrix._32, _worldMatrix._33);

	_right.Normalize();
	_up   .Normalize();
	_look .Normalize();

	int a = 0;
}

void Transform::LateUpdate()
{
}

void Transform::SetPosition(const Vector3& position)
{
	_position = position;
	Update();
}

void Transform::SetScale(const Vector3& scale)
{
	_scale = scale;
	Update();
}

void Transform::SetRotation(const Quaternion& rotation)
{
	_rotation = rotation;
	Update();	
}

void Transform::Translation(const Vector3& dir, float speed)
{
	_position += dir * (Timer::Instance().DeltaTime() * speed);
	Update();
}
