#pragma once

#include <d3d11.h>
#include <d3dx10math.h>

namespace OK
{
    struct RenderingContext;

    class Shader
    {
    public:
        Shader(const RenderingContext& renderingContext, const OK::char8* shaderName, const OK::char8* vertexShaderFile, const OK::char8* pixelShaderFile);
        ~Shader();

        const String& GetName() const { return m_Name; }

        void RunShader(const RenderingContext& renderingContext, OK::u32 indexCount);

    private:
        struct MatrixBufferData
        {
            D3DXMATRIX world;
            D3DXMATRIX view;
            D3DXMATRIX projection;
        };

        void InitializeShader(const RenderingContext& renderingContext, const OK::char8* vertexShaderFile, const OK::char8* pixelShaderFile);
        void ShutdownShader();
        void SetShaderParameters(const RenderingContext& renderingContext);
        void RenderShaderInternal(const RenderingContext& renderingContext, OK::s32 indexCount);

        String m_Name;
        ID3D11VertexShader* m_VertexShader;
        ID3D11PixelShader* m_PixelShader;
        ID3D11InputLayout* m_Layout;
        ID3D11Buffer* m_MatrixBuffer;
    };
}