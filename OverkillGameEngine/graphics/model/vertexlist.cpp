#include <stdafx.h>
#include <graphics\model\vertexlist.h>

#include <core\io\parsers\json\jsonnode.h>
#include <graphics\renderingcontext.h>

namespace OK
{
    VertexList::VertexList()
        : m_VertexBuffer{ nullptr }
        , m_IndexBuffer{ nullptr }
        , m_VertexCount{ 0 }
        , m_IndexCount{ 0 }
    {
    }

    VertexList::~VertexList()
    {
        if (m_VertexBuffer != nullptr)
        {
            m_VertexBuffer->Release();
            m_VertexBuffer = nullptr;
        }
        if (m_IndexBuffer != nullptr)
        {
            m_IndexBuffer->Release();
            m_IndexBuffer = nullptr;
        }
    }

    EResult VertexList::LoadVertexList(const RenderingContext& renderingContext, JSONNode* vertexListNode)
    {
        JSONNode* vertexDataNode = vertexListNode->GetNode("VertexList");
        JSONNode* indexDataNode = vertexListNode->GetNode("IndexList");
        okAssert(vertexDataNode != nullptr, "Could not find Vertex List node in game data file.");
        okAssert(indexDataNode != nullptr, "Could not find Index List node in game data file.");
        vertexDataNode->ComputeSubNodes();
        indexDataNode->ComputeSubNodes();
        okAssert(vertexDataNode->GetNodeType() == JSONNode::ENodeType::Array, "Vertex List node in must be of type Array.");
        okAssert(indexDataNode->GetNodeType() == JSONNode::ENodeType::Array, "Index List node in must be of type Array.");

        Array<VertexData> vertexData;
        OK::u32 vertexCount = vertexDataNode->GetArrayNodeSize();
        vertexData.Reserve(vertexCount);
        for (OK::u32 i = 0; i < vertexCount; ++i)
        {
            JSONNode* vertexNode = vertexDataNode->GetNodeAtIndex(i);
            vertexNode->ComputeSubNodes();

            VertexData& newVertexData{ vertexData.Grow() };
            OK::f32 x{ vertexNode->GetValue<OK::f32>("x") };
            OK::f32 y{ vertexNode->GetValue<OK::f32>("y") };
            OK::f32 z{ vertexNode->GetValue<OK::f32>("z") };
            newVertexData.m_Position = OK::Vec4{ x, y, z };

            OK::f32 r{ vertexNode->GetValue<OK::f32>("r") };
            OK::f32 g{ vertexNode->GetValue<OK::f32>("g") };
            OK::f32 b{ vertexNode->GetValue<OK::f32>("b") };
            OK::f32 a{ vertexNode->GetValue<OK::f32>("a") };
            newVertexData.m_Color = OK::Vec4{ r, g, b, a };

            OK::f32 u{ vertexNode->GetValue<OK::f32>("u") };
            OK::f32 v{ vertexNode->GetValue<OK::f32>("v") };
            newVertexData.m_TextureCoords = OK::Vec4{ u, v };
        }
        SetVertexList(renderingContext, vertexData);

        Array<OK::u32> indexData;
        OK::u32 indexCount = indexDataNode->GetArrayNodeSize();
        indexData.Reserve(vertexCount);
        for (OK::u32 i = 0; i < indexCount; ++i)
        {
            JSONNode* indexNode = indexDataNode->GetNodeAtIndex(i);
            indexNode->ComputeSubNodes();
            indexData.Add(indexNode->GetValue<OK::u32>("index"));
        }
        SetIndexList(renderingContext, indexData);

        return EResult::Success;
    }

    void VertexList::SetVertexList(const RenderingContext& renderingContext, const Array<VertexData>& vertexData)
    {
        D3D11_BUFFER_DESC vertexBufferDesc;
        D3D11_SUBRESOURCE_DATA vertexBufferData;

        m_VertexCount = vertexData.GetSize();

        vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        vertexBufferDesc.ByteWidth = sizeof(VertexData) * m_VertexCount;
        vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        vertexBufferDesc.CPUAccessFlags = 0;
        vertexBufferDesc.MiscFlags = 0;
        vertexBufferDesc.StructureByteStride = 0;

        vertexBufferData.pSysMem = vertexData.begin();
        vertexBufferData.SysMemPitch = 0;
        vertexBufferData.SysMemSlicePitch = 0;

        HRESULT result = renderingContext.m_Device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &m_VertexBuffer);
        okAssert(SUCCEEDED(result), "Failed to load vertex buffer.");
    }

    void VertexList::SetIndexList(const RenderingContext& renderingContext, const Array<OK::u32>& indexList)
    {
        D3D11_BUFFER_DESC indexBufferDesc;
        D3D11_SUBRESOURCE_DATA indexData;

        m_IndexCount = indexList.GetSize();

        indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        indexBufferDesc.ByteWidth = sizeof(OK::u32) * m_IndexCount;
        indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
        indexBufferDesc.CPUAccessFlags = 0;
        indexBufferDesc.MiscFlags = 0;
        indexBufferDesc.StructureByteStride = 0;

        indexData.pSysMem = indexList.begin();
        indexData.SysMemPitch = 0;
        indexData.SysMemSlicePitch = 0;

        HRESULT result = renderingContext.m_Device->CreateBuffer(&indexBufferDesc, &indexData, &m_IndexBuffer);
        okAssert(SUCCEEDED(result), "Failed to load index buffer.");
    }
}