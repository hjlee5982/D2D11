#include "pch.h"
#include "Mesh.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "GeometryHelper.h"

void Mesh::CreateMesh(EMeshType type)
{
    _geometry = makeSptr<Geometry<VertexTextureData>>();

    switch (type)
    {
    case EMeshType::Square:
        GeometryHelper::CreateSquare(_geometry);
        break;

    case EMeshType::Cube:
        break;

    case EMeshType::Sphere:
        break;

    case EMeshType::End:
        break;

    default:
        break;
    }

    CreateBuffers();
}

void Mesh::Bind()
{
    _vertexBuffer->PushData();
    _indexBuffer->PushData();

    Device::Instance().GetContext()->DrawIndexed(_indexBuffer->GetIndexCount(), 0, 0);
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
