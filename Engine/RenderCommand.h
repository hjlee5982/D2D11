#pragma once

struct SpriteRendererCommand
{
	Matrix          WorldMatrix;
	sptr<TMeshBase> Mesh;
	sptr<Material>  Material;
	i32             OrderInLayer;
};

struct RenderContext
{
	List<SpriteRendererCommand> spriteCmds;
};