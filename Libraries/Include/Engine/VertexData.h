#pragma once

struct VertexColliderData
{
	Vector3 position = { 0.f, 0.f, 0.f };
	Vector4	color    = { 0.f, 1.f, 0.f, 1.f };
};

struct VertexTextureData
{
	Vector3 position = { 0.f, 0.f, 0.f };
	Vector2 uv       = { 0.f, 0.f      };
};