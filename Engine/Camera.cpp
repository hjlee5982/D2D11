#include "pch.h"
#include "Camera.h"

void Camera::Awake()
{
	_near = 0.1f;
	_far  = 300.f;
	_fov  = ::XMConvertToRadians(60.f);

	_width = Device::Instance().GetWidth();
	_height = Device::Instance().GetHeight();

	//Global::ProjMatrix = ::XMMatrixPerspectiveFovLH(_fov, _width / _height, _near, _far);
	Global::ProjMatrix = ::XMMatrixOrthographicLH(_width, _height, 1.f, 10.f);
}

void Camera::Start()
{
}

void Camera::Update()
{
	Global::ViewMatrix = gameObject->transform->GetWorldMatrix().Invert();
	// Global::ProjMatrix = ::XMMatrixPerspectiveFovLH(_fov, _width / _height, _near, _far);
	Global::ProjMatrix = ::XMMatrixOrthographicLH(_width, _height, 1.f, 10.f);
}

void Camera::LateUpdate()
{
}