#pragma once

#include <d3d11.h>
#include <d3dx10math.h>
#include <graphics\model\vertexdata.h>

namespace OK
{
    struct RenderingContext;

    struct VertexList
    {
    public:
        VertexList();
        ~VertexList();

        void SetVertexList(const RenderingContext& renderingContext, const Array<VertexData>& vertexList);
        void SetIndexList(const RenderingContext& renderingContext, const Array<OK::u32>& indexList);

        ID3D11Buffer* GetVertexBuffer() { return m_VertexBuffer; }
        ID3D11Buffer* GetIndexBuffer() { return m_IndexBuffer; }
        OK::u32 GetIndexCount() const { return m_IndexCount; }

    private:
        ID3D11Buffer* m_VertexBuffer;
        ID3D11Buffer* m_IndexBuffer;
        OK::u32 m_VertexCount;
        OK::u32 m_IndexCount;
    };
}