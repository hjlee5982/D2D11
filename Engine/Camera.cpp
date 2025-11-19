#include "pch.h"
#include "Camera.h"

void Camera::MakeJson()
{
}

void Camera::LoadJson(const nlohmann::json& json)
{
}

void Camera::Awake()
{
	_near = 0.3f;
	_far  = 1000.f;
	_fov  = ::XMConvertToRadians(60.f);

	_width  = Device::Instance().GetWidth();
	_height = Device::Instance().GetHeight();

	f32 orthoSize = 5.f;
	f32 aspect = _width / _height;

	//Global::ProjMatrix = ::XMMatrixPerspectiveFovLH(_fov, _width / _height, _near, _far);
	//Global::ProjMatrix = ::XMMatrixOrthographicLH(_width, _height, _near, _far);
	Global::ProjMatrix = ::XMMatrixOrthographicLH(orthoSize * aspect * 2, orthoSize * 2, _near, _far);

	Owner()->transform->SetPosition(Vector3(0.f, 0.f, -_far / 2));
}

void Camera::Update()
{
	f32 orthoSize = 5.f;
	f32 aspect = _width / _height;

	Global::ViewMatrix = Owner()->transform->GetWorldMatrix().Invert();
	// Global::ProjMatrix = ::XMMatrixPerspectiveFovLH(_fov, _width / _height, _near, _far);
	//Global::ProjMatrix = ::XMMatrixOrthographicLH(_width, _height, _near, _far);
	Global::ProjMatrix = ::XMMatrixOrthographicLH(orthoSize * aspect * 2, orthoSize * 2, _near, _far);
}