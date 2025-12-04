#include "pch.h"
#include "GeometryHelper.h"

void GeometryHelper::CreateSquare(sptr<Geometry<VertexColliderData>> geometry)
{
	f32 padding = 0.0f;

	List<VertexColliderData> vtx;
	{
		vtx.push_back({ Vector3(-0.5f - padding,  0.5f + padding, 0.f) });
		vtx.push_back({ Vector3( 0.5f + padding,  0.5f + padding, 0.f) });
		vtx.push_back({ Vector3( 0.5f + padding, -0.5f - padding, 0.f) });
		vtx.push_back({ Vector3(-0.5f - padding, -0.5f - padding, 0.f) });

		geometry->SetVertices(vtx);
	}

	List<u32> idx = { 0, 1, 1, 2, 2, 3, 3, 0 };
	{
		geometry->SetIndices(idx);
	}
}

void GeometryHelper::CreateSquare(sptr<Geometry<VertexTextureData>> geometry)
{
	List<VertexTextureData> vtx;
	{
		vtx.push_back({ Vector3(-0.5f,  0.5f, 0.f), Vector2(0.f, 0.f) });
		vtx.push_back({ Vector3( 0.5f,  0.5f, 0.f), Vector2(1.f, 0.f) });
		vtx.push_back({ Vector3( 0.5f, -0.5f, 0.f), Vector2(1.f, 1.f) });
		vtx.push_back({ Vector3(-0.5f, -0.5f, 0.f), Vector2(0.f, 1.f) });

		geometry->SetVertices(vtx);
	}

	List<u32> idx = { 0, 1, 2, 0, 2, 3 };
	{
		geometry->SetIndices(idx);
	}
}

void GeometryHelper::CreateSquare(sptr<Geometry<VertexUIData>> geometry)
{
	List<VertexUIData> vtx;
	{
		vtx.push_back({ Vector3(-0.5f,  0.5f, 0.f), Vector2(0.f, 0.f), Vector4(1.f, 1.f, 1.f, 1.f) });
		vtx.push_back({ Vector3( 0.5f,  0.5f, 0.f), Vector2(1.f, 0.f), Vector4(1.f, 1.f, 1.f, 1.f) });
		vtx.push_back({ Vector3( 0.5f, -0.5f, 0.f), Vector2(1.f, 1.f), Vector4(1.f, 1.f, 1.f, 1.f) });
		vtx.push_back({ Vector3(-0.5f, -0.5f, 0.f), Vector2(0.f, 1.f), Vector4(1.f, 1.f, 1.f, 1.f) });

		geometry->SetVertices(vtx);
	}

	List<u32> idx = { 0, 1, 2, 0, 2, 3 };
	{
		geometry->SetIndices(idx);
	}
}

void GeometryHelper::CreateCircle(sptr<Geometry<VertexColliderData>> geometry)
{
}

void GeometryHelper::CreateCircle(sptr<Geometry<VertexTextureData>> geometry)
{
}

void GeometryHelper::CreateCircle(sptr<Geometry<VertexUIData>> geometry)
{
}

void GeometryHelper::CreateCube(sptr<Geometry<VertexColliderData>> geometry)
{
}

void GeometryHelper::CreateCube(sptr<Geometry<VertexTextureData>> geometry)
{
}

void GeometryHelper::CreateCube(sptr<Geometry<VertexUIData>> geometry)
{
}

void GeometryHelper::CreateSphere(sptr<Geometry<VertexColliderData>> geometry)
{
}

void GeometryHelper::CreateSphere(sptr<Geometry<VertexTextureData>> geometry)
{
}

void GeometryHelper::CreateSphere(sptr<Geometry<VertexUIData>> geometry)
{
}