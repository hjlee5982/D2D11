#pragma once

#include "Renderer.h"

class Mesh;
class Texture;
class Material;
class TMeshBase;

class SpriteRenderer : public Renderer, public std::enable_shared_from_this<SpriteRenderer>
{
public:
	virtual void Init() override;
public:
	virtual void CollectRenderData(RenderContext& ctx) override;
public:
	int OrderInLayer = 0;
};