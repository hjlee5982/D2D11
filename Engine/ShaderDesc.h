#pragma once

#include "ConstantBuffer.h"

class Shader;

struct TRANSFORM_DATA
{
	Matrix4x4 gWorldMatrix = Matrix4x4::Identity;
	Matrix4x4 gViewMatrix  = Matrix4x4::Identity;
	Matrix4x4 gProjMatrix  = Matrix4x4::Identity;

	Matrix4x4 gCameraWorldMatrix = Matrix4x4::Identity;

	static const UINT registerNum = 0;
};

struct LIGHT_DATA
{
	Vector3 direction;
	Color ambient  = Color(1.f, 1.f, 1.f, 1.f);
	Color diffuse  = Color(1.f, 1.f, 1.f, 1.f);
	Color specular = Color(1.f, 1.f, 1.f, 1.f);
	Color emissive = Color(1.f, 1.f, 1.f, 1.f);

	f32 padding;

	static const UINT registerNum = 1;
};

struct GLOBAL_DATA
{
	Color   color;
	Vector4 test;

	static const UINT registerNum = 2;
};

struct MATERIAL_DATA
{
	Color ambient = Color(1.f, 1.f, 1.f, 1.f);
	Color diffuse = Color(1.f, 1.f, 1.f, 1.f);
	Color specular = Color(1.f, 1.f, 1.f, 1.f);
	Color emissive = Color(1.f, 1.f, 1.f, 1.f);

	static const UINT registerNum = 3;
};

