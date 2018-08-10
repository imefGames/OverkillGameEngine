#include <stdafx.h>
#include <graphics\texture\texture.h>

#include <graphics\renderingcontext.h>

namespace OK
{
    Texture::Texture()
        : m_D3DTexture{ nullptr }
    {
    }

    Texture::~Texture()
    {
    }

    EResult Texture::Load(const RenderingContext& renderingContext, const String& textureName, const String& texturePath)
    {
        m_Name = textureName;
        HRESULT result = D3DX11CreateShaderResourceViewFromFile(renderingContext.m_Device, texturePath.begin(), NULL, NULL, &m_D3DTexture, NULL);
        return (SUCCEEDED(result) ? EResult::Success : EResult::Failure);
    }

    void Texture::Unload()
    {
        if (m_D3DTexture != nullptr)
        {
            m_D3DTexture->Release();
            m_D3DTexture = nullptr;
        }
    }
}