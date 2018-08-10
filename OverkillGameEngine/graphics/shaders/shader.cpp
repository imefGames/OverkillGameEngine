#include <stdafx.h>
#include <graphics\shaders\shader.h>

#include <graphics\renderingcontext.h>
#include <d3dx11async.h>

namespace OK
{
    Shader::Shader(const OK::char8* shaderName)
        : m_Name{ shaderName }
    {
    }

    Shader::~Shader()
    {
    }

    void Shader::RunShader(const RenderingContext& renderingContext, const ShaderRenderData& shaderRenderData)
    {
        SetShaderParameters(renderingContext, shaderRenderData);
        RenderShaderInternal(renderingContext, shaderRenderData);
    }

    void Shader::ShutdownShader()
    {
        if (m_MatrixBuffer)
        {
            m_MatrixBuffer->Release();
            m_MatrixBuffer = nullptr;
        }
        if (m_Layout)
        {
            m_Layout->Release();
            m_Layout = nullptr;
        }
        if (m_PixelShader)
        {
            m_PixelShader->Release();
            m_PixelShader = nullptr;
        }
        if (m_VertexShader)
        {
            m_VertexShader->Release();
            m_VertexShader = nullptr;
        }
    }
}