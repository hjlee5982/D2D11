#pragma once

#include "Geometry.h"
#include "UIComponent.h"
#include "VertexData.h"

class Material;
class IndexBuffer;
class VertexBuffer;

class UIText : public UIComponent
{
public:
	void Init();
	void Update();
public:
	void Text(const wstring& text)
	{
		_text = text; Update();
	}
public:
	sptr<Geometry<VertexTextureData>> _geometry;
private:
	wstring  _text;
	Vector2 _position;
	f32     _scale = 1.0f;
	Color   _color = Color(1.f, 1.f, 1.f, 1.f);
};

