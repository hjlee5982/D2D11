#pragma once

#include "Geometry.h"
#include "VertexData.h"

class GeometryHelper
{
public:
	static void CreateSquare(sptr<Geometry<VertexTextureData>> geometry);
};