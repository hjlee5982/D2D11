#include "pch.h"
#include "Mesh.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "GeometryHelper.h"

void Mesh::Load(const wstring& path)
{
}

void Mesh::Save(const wstring& path)
{
}

void Mesh::CreateSquare()
{
    _geometry = makeSptr<Geometry<VertexTextureData>>();
    GeometryHelper::CreateSquare(_geometry);
    CreateBuffers();
}

void Mesh::PushData()
{
    _vertexBuffer->PushData();
    _indexBuffer->PushData();
}

void Mesh::CreateBuffers()
{
    _vertexBuffer = makeSptr<VertexBuffer>();
    _vertexBuffer->Create(_geometry->GetVertices());

    _indexBuffer = makeSptr<IndexBuffer>();
    _indexBuffer->Create(_geometry->GetIndices());
}

sptr<VertexBuffer> Mesh::GetVertexBuffer()
{
    return _vertexBuffer;
}

sptr<IndexBuffer> Mesh::GetIndexBuffer()
{
    return _indexBuffer;
}

sptr<Geometry<VertexTextureData>> Mesh::GetGeometry()
{
    return _geometry;
}
