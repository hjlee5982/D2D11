#pragma once

#include "ConstantBuffer.h"

class Shader;

struct TransformData
{
	Matrix4x4 gWorldMatrix = Matrix4x4::Identity;
	Matrix4x4 gViewMatrix  = Matrix4x4::Identity;
	Matrix4x4 gProjMatrix  = Matrix4x4::Identity;

	Matrix4x4 gCameraWorldMatrix = Matrix4x4::Identity;
};

struct LightData
{
	Vector3 direction;
	Color ambient  = Color(1.f, 1.f, 1.f, 1.f);
	Color diffuse  = Color(1.f, 1.f, 1.f, 1.f);
	Color specular = Color(1.f, 1.f, 1.f, 1.f);
	Color emissive = Color(1.f, 1.f, 1.f, 1.f);

	f32 padding;
};

struct GlobalData
{
	Color   color;
	Vector4 test;
};

struct MaterialData
{
	Color ambient = Color(1.f, 1.f, 1.f, 1.f);
	Color diffuse = Color(1.f, 1.f, 1.f, 1.f);
	Color specular = Color(1.f, 1.f, 1.f, 1.f);
	Color emissive = Color(1.f, 1.f, 1.f, 1.f);
};

