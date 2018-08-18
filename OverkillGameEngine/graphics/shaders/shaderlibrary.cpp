#include <stdafx.h>
#include <graphics\shaders\shaderlibrary.h>

#include <graphics\shaders\colorshader.h>
#include <graphics\shaders\lightshader.h>
#include <graphics\shaders\lightspecularshader.h>
#include <graphics\shaders\textureshader.h>

namespace OK
{

    template<typename ShaderType>
    void ShaderLibrary::RegisterShader(const RenderingContext& renderingContext, const OK::char8* shaderName, const OK::char8* vertexShaderFile, const OK::char8* pixelShaderFile)
    {
        Shader* newShader{ new ShaderType{ shaderName } };
        newShader->InitializeShader(renderingContext, vertexShaderFile, pixelShaderFile);
        m_Shaders.Add(newShader);
    }

    void ShaderLibrary::PopulateLibrary(const RenderingContext& renderingContext)
    {
        RegisterShader<ColorShader>(renderingContext, "Color", "graphics/shaders/color.vs", "graphics/shaders/color.ps");
        RegisterShader<LightShader>(renderingContext, "Light", "graphics/shaders/light.vs", "graphics/shaders/light.ps");
        RegisterShader<LightSpecularShader>(renderingContext, "SpecularLight", "graphics/shaders/lightspecular.vs", "graphics/shaders/lightspecular.ps");
        RegisterShader<TextureShader>(renderingContext, "Texture", "graphics/shaders/texture.vs", "graphics/shaders/texture.ps");
    }

    void ShaderLibrary::ClearLibrary()
    {
        for (Shader* shader : m_Shaders)
        {
            shader->ShutdownShader();
        }
        m_Shaders.DeleteAll();
    }

    Shader* ShaderLibrary::FindShader(const OK::char8* shaderName)
    {
        auto findByName = [shaderName](const Shader* shader)
        {
            return OK::MemEqual(shader->GetName().begin(), shaderName, shader->GetName().GetSize());
        };
        auto foundIt = OK::FindIf(m_Shaders.begin(), m_Shaders.end(), findByName);
        return(foundIt != m_Shaders.end() ? *foundIt : nullptr);
    }
}