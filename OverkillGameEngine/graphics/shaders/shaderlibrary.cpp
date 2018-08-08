#include <stdafx.h>
#include <graphics\shaders\shaderlibrary.h>

#include <graphics\shaders\shader.h>

namespace OK
{
    void ShaderLibrary::PopulateLibrary(const RenderingContext& renderingContext)
    {
        m_Shaders.Add(new Shader{ renderingContext, " \"Color\"", "graphics/shaders/color.vs", "graphics/shaders/color.ps" });
    }

    void ShaderLibrary::ClearLibrary()
    {
        m_Shaders.DeleteAll();
    }

    Shader* ShaderLibrary::FindShader(const OK::char8* shaderName)
    {
        auto findByName = [shaderName](const Shader* shader)
        {
            return OK::MemEqual(shader->GetName().begin(), shaderName, shader->GetName().GetSize());
        };
        auto foundIt = OK::FindIf(m_Shaders.begin(), m_Shaders.end(), findByName);
        return(foundIt != m_Shaders.end() ? *foundIt : 0);
    }
}