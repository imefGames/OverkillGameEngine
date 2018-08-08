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
        PointerArray<Shader> m_Shaders;
    };
}