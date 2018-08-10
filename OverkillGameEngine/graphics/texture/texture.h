#pragma once

#include <d3d11.h>
#include <d3dx11tex.h>

namespace OK
{
    struct RenderingContext;

    class Texture
    {
    public:
        Texture();
        ~Texture();

        EResult Load(const RenderingContext& renderingContext, const String& textureName, const String& texturePath);
        void Unload();

        const String& GetName() const { return m_Name; }
        ID3D11ShaderResourceView* const GetTexture() const { return m_D3DTexture; }

    private:
        String m_Name;
        ID3D11ShaderResourceView* m_D3DTexture;
    };
}