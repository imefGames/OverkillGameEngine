#pragma once

#include <core\containers\pointerarray.h>

namespace OK
{
    class Shader;
    struct RenderingContext;

    class ShaderLibrary
    {
    public:
        void PopulateLibrary(const RenderingContext& renderingContext);
        void ClearLibrary();
        Shader* FindShader(const OK::char8* shaderName);

    private:
        template<typename ShaderType>
        void RegisterShader(const RenderingContext& renderingContext, const OK::char8* shaderName, const OK::char8* vertexShaderFile, const OK::char8* pixelShaderFile);

        PointerArray<Shader> m_Shaders;
    };
}