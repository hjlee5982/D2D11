#include "pch.h"
#include "GeometryHelper.h"

void GeometryHelper::CreateSquare(sptr<Geometry<VertexTextureData>> geometry)
{
	List<VertexTextureData> vtx;
	{
		vtx.resize(4);

		vtx[0].position = Vector3(-0.5f, 0.5f, 0.f);
		vtx[0].uv       = Vector2( 0.0f, 0.0f      );

		vtx[1].position = Vector3(0.5f, 0.5f, 0.f);
		vtx[1].uv       = Vector2(1.0f, 0.0f      );

		vtx[2].position = Vector3(0.5f, -0.5f, 0.f);
		vtx[2].uv       = Vector2(1.0f,  1.0f      );

		vtx[3].position = Vector3(-0.5f, -0.5f, 0.f);
		vtx[3].uv       = Vector2( 0.0f,  1.0f     );

		geometry->SetVertices(vtx);
	}

	List<u32> idx = { 0, 1, 2, 0, 2, 3 };
	{
		geometry->SetIndices(idx);
	}
}
