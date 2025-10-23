#pragma once

#include "Geometry.h"

class VertexBuffer;
class IndexBuffer;

enum class EMeshType
{
	Square,
	Cube,
	Sphere,

	End
};

class Mesh : public Asset
{
public:
	Mesh() : Asset(EAssetType::Mesh) {}
public:
	virtual void Load(const wstring& path) override {}
	virtual void Save(const wstring& path) override {}
public:
	void CreateMesh(EMeshType type);
	void Bind();
private:
	void CreateBuffers();
public:
	sptr<VertexBuffer>                GetVertexBuffer();
	sptr<IndexBuffer>                 GetIndexBuffer();
	sptr<Geometry<VertexTextureData>> GetGeometry();
private:
	sptr<VertexBuffer>                _vertexBuffer;
	sptr<IndexBuffer>                 _indexBuffer;
	sptr<Geometry<VertexTextureData>> _geometry;
};