#pragma once

#include <graphics\texture\texture.h>

namespace OK
{
    class JSONNode;
    struct RenderingContext;

    class TextureLibrary
    {
    public:
        EResult RegisterTextures(const RenderingContext& renderingContext, JSONNode* textureLibraryNode);
        void ClearLibrary();
        Texture* FindTexture(const OK::char8* textureName);

    private:
        Array<Texture> m_Textures;
    };
}