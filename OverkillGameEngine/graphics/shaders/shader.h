#pragma once

#include <d3d11.h>
#include <d3dx10math.h>

namespace OK
{
    class Texture;
    struct RenderingContext;

    struct ShaderRenderData
    {
        OK::u32 m_IndexCount = 0;
        Texture* m_Texture = nullptr;
    };

    class Shader
    {
    public:
        virtual ~Shader();

        const String& GetName() const { return m_Name; }

        virtual void InitializeShader(const RenderingContext& renderingContext, const OK::char8* vertexShaderFile, const OK::char8* pixelShaderFile) = 0;
        virtual void ShutdownShader();
        void RunShader(const RenderingContext& renderingContext, const ShaderRenderData& shaderRenderData);

    protected:
        Shader(const OK::char8* shaderName);

        struct MatrixBufferData
        {
            D3DXMATRIX world;
            D3DXMATRIX view;
            D3DXMATRIX projection;
        };

        virtual void SetShaderParameters(const RenderingContext& renderingContext, const ShaderRenderData& shaderRenderData) = 0;
        virtual void RenderShaderInternal(const RenderingContext& renderingContext, const ShaderRenderData& shaderRenderData) = 0;

        String m_Name;
        ID3D11VertexShader* m_VertexShader;
        ID3D11PixelShader* m_PixelShader;
        ID3D11InputLayout* m_Layout;
        ID3D11Buffer* m_MatrixBuffer;
    };
}