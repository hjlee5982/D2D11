#pragma once

#include "Geometry.h"
#include "TMesh.h"
#include "UIComponent.h"
#include "VertexData.h"

class Material;
class IndexBuffer;
class VertexBuffer;

class UIText : public UIComponent, public std::enable_shared_from_this<UIText>
{
public:
	void Init();
public:
	void Text(const wstring& text);
public:
	sptr<Geometry<VertexUIData>> _geometry;
private:
	Vector2 _position;
	f32     _scale = 1.0f;
	Color   _color = Color(1.f, 1.f, 1.f, 1.f);
};

