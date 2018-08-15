#pragma once

#include <d3d11.h>
#include <d3dx10math.h>

#include <core\math\vectors.h>
#include <graphics\shaders\shader.h>

namespace OK
{
    struct RenderingContext;

    class LightShader : public Shader
    {
    public:
        struct LightBufferData
        {
            OK::Vec4 m_AmbientColor;
            OK::Vec4 m_DiffuseColor;
            OK::Vec4 m_LightDirection;
        };

        LightShader(const OK::char8* shaderName);

    private:
        void InitializeShader(const RenderingContext& renderingContext, const OK::char8* vertexShaderFile, const OK::char8* pixelShaderFile) override;
        void ShutdownShader() override;
        void SetShaderParameters(const RenderingContext& renderingContext, const ShaderRenderData& shaderRenderData) override;
        void RenderShaderInternal(const RenderingContext& renderingContext, const ShaderRenderData& shaderRenderData) override;

        ID3D11SamplerState* m_SampleState;
        ID3D11Buffer* m_LightBuffer;
    };
}