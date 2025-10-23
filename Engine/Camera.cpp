#include "pch.h"
#include "Camera.h"

Matrix Camera::ViewMatrix = Matrix::Identity;
Matrix Camera::ProjMatrix = Matrix::Identity;

void Camera::SetOwner(sptr<class GameObject> owner)
{
	gameObject = owner;
}

void Camera::Update()
{
	ViewMatrix = gameObject->transform->worldMatrix.Invert();
	ProjMatrix = ::XMMatrixPerspectiveFovLH(_fov, _width / _height, _near, _far);
	// ProjMatrix = ::XMMatrixOrthographicLH(_width, _height, 1.f, 10.f);
}

void Camera::SetCameraOption(f32 Near, f32 Far, f32 fov)
{
	_near = Near;
	_far  = Far;
	_fov  = ::XMConvertToRadians(fov);

	_width  = Device::Instance().GetWidth();
	_height = Device::Instance().GetHeight();

	ProjMatrix = ::XMMatrixPerspectiveFovLH(_fov, _width / _height, _near, _far);
	// ProjMatrix = ::XMMatrixOrthographicLH(_width, _height, 1.f, 10.f);
}