#pragma once

struct VertexTextureData
{
	Vector3 position = { 0.f, 0.f, 0.f };
	Vector2 uv       = { 0.f, 0.f      };
};

struct VertexUIData
{
	Vector2 position = { 0.f, 0.f };
	Vector2 uv       = { 0.f, 0.f};
	Vector4 color    = { 0.f, 0.f, 0.f, 0.f };
};