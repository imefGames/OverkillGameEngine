#include <stdafx.h>
#include <graphics\model\vertexlist.h>

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