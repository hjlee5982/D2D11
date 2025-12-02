#include "pch.h"
#include "UIText.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "Material.h"
#include "AssetManager.h"
#include "VertexData.h"
#include "FontManager.h"
#include "Geometry.h"
#include "Mesh.h"

void UIText::Init()
{
	_mesh     = makeSptr<Mesh>();
	_geometry = makeSptr<Geometry<VertexTextureData>>();
	_material = ASSET.Get<Material>(L"Material_Font", true);

	RENDERER.AddUI(Owner());
}

void UIText::Update()
{
	List<VertexTextureData> vtx;
	List<u32> idx;

	vtx.reserve(_text.size() * 4);
	idx.reserve(_text.size() * 6);

	f32 cursorX = -0.5f;

	for (i32 i = 0; i < _text.size(); ++i)
	{
		auto iter = FONT.glyphs.find((int)_text[i]);

		if (iter == FONT.glyphs.end())
		{
			continue;
		}

		f32 scale = 0.015f;

		const Glyph& g = iter->second;

		f32 witdh  = FONT._textureWidth;
		f32 height = FONT._textureHeight;

		f32 x0 = cursorX;
		f32 x1 = cursorX + g.witdh * scale;
		f32 y0 =  0.5f;
		f32 y1 = -g.height * scale;

		vtx.push_back({ Vector3(x0,y0, 0.f), Vector2(g.u0, g.v0) });
		vtx.push_back({ Vector3(x1,y0, 0.f), Vector2(g.u1, g.v0) });
		vtx.push_back({ Vector3(x1,y1, 0.f), Vector2(g.u1, g.v1) });
		vtx.push_back({ Vector3(x0,y1, 0.f), Vector2(g.u0, g.v1) });

		i32 base = i * 4;
		idx.push_back(base + 0);
		idx.push_back(base + 1);
		idx.push_back(base + 2);
		idx.push_back(base + 0);
		idx.push_back(base + 2);
		idx.push_back(base + 3);

		cursorX += g.xAdvance * scale + 0.1f;
	}

	_geometry->SetVertices(vtx);
	_geometry->SetIndices(idx);

	_mesh->CreateMesh(_geometry);
}