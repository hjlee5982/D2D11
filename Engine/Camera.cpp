#include "pch.h"
#include "Camera.h"

void Camera::MakeJson()
{
}

void Camera::LoadJson()
{
}

void Camera::Awake()
{
	_near = 0.1f;
	_far  = 300.f;
	_fov  = ::XMConvertToRadians(60.f);

	_width  = Device::Instance().GetWidth();
	_height = Device::Instance().GetHeight();

	//Global::ProjMatrix = ::XMMatrixPerspectiveFovLH(_fov, _width / _height, _near, _far);
	Global::ProjMatrix = ::XMMatrixOrthographicLH(_width, _height, _near, _far);

	Owner()->transform->SetPosition(Vector3(0.f, 0.f, -_far / 2));
}

void Camera::Update()
{
	Global::ViewMatrix = Owner()->transform->GetWorldMatrix().Invert();
	// Global::ProjMatrix = ::XMMatrixPerspectiveFovLH(_fov, _width / _height, _near, _far);
	Global::ProjMatrix = ::XMMatrixOrthographicLH(_width, _height, _near, _far);
}