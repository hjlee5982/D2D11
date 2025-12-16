#pragma once

struct SpriteRendererCommand
{
	Matrix				  WorldMatrix;
	sptr<class TMeshBase> Mesh;
	sptr<class Material>  Material;
	i32					  OrderInLayer;
};

struct RenderContext
{
	List<SpriteRendererCommand> spriteCmds;
};