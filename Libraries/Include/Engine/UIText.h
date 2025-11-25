#pragma once

#include "Geometry.h"
#include "Component.h"
#include "VertexData.h"

class Material;
class IndexBuffer;
class VertexBuffer;

class UIText : public Component
{
public:
	void Init();
	void Update();
public:
	void Text(const wstring& text)
	{
		_text = text;
		Update();
	}
private:
	void CreateBuffer();
public:
	sptr<VertexBuffer>           _vertexBuffer;
	sptr<IndexBuffer>            _indexBuffer;
	sptr<Geometry<VertexTextureData>> _geometry;
	sptr<Material> _material;
public:
	sptr<Material> GetMaterial();
private:
	wstring  _text;
	Vector2 _position;
	f32     _scale = 1.0f;
	Color   _color = Color(1.f, 1.f, 1.f, 1.f);
};

