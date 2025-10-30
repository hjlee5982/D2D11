#include "pch.h"
#include "Transform.h"

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
}

void Transform::UpdateLocalMatrix()
{
	Matrix scale    = Matrix::CreateScale(_localScale);
	Matrix rotation = Matrix::CreateFromQuaternion(_localRotation);
	Matrix position = Matrix::CreateTranslation(_localPosition);

	_localMatrix = scale * rotation * position;
}

void Transform::SetLocalMatrix(const Matrix& localMatrix)
{
	_localMatrix = localMatrix;
	UpdateLocalMatrix();
}

void Transform::SetLocalPosition(const Vector3& localPosition)
{
	_localPosition = localPosition;
	UpdateLocalMatrix();
}

void Transform::SetLocalScale(const Vector3& localScale)
{
	_localScale = localScale;
	UpdateLocalMatrix();
}

void Transform::SetLocalRotaion(const Quaternion& localRotation)
{
	_localRotation = localRotation;
	UpdateLocalMatrix();
}

void Transform::SetWorldMatrix(const Matrix& worldMatrix)
{
	_worldMatrix = worldMatrix;

	_right = Vector3(_worldMatrix._11, _worldMatrix._12, _worldMatrix._13);
	_up    = Vector3(_worldMatrix._21, _worldMatrix._22, _worldMatrix._23);
	_look  = Vector3(_worldMatrix._31, _worldMatrix._32, _worldMatrix._33);

	_right.Normalize();
	_up.Normalize();
	_look.Normalize();
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
	_position += dir * (TIMER.DeltaTime() * speed);
	Update();
}
