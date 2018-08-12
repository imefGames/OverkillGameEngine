#include <stdafx.h>
#include <graphics\texture\texturelibrary.h>

#include <core\io\parsers\json\jsonnode.h>

namespace OK
{
    EResult TextureLibrary::RegisterTextures(const RenderingContext& renderingContext, const JSONNode& textureLibraryNode)
    {
        EResult loadResult{ EResult::Success };

        const JSONNode* textureListNode{ textureLibraryNode["TextureList"] };
        m_Textures.Reserve(textureListNode->GetSubNodeCount());
        for (const JSONNode& textureNode : *textureListNode)
        {
            const JSONNode* textureNameNode = textureNode["Name"];
            const JSONNode* texturePathNode = textureNode["Path"];

            String textureName;
            textureName.Resize(textureNameNode->GetValue().GetLength());
            OK::MemCopy(textureNameNode->GetValue().begin(), textureName.begin(), textureName.GetSize());

            String texturePath;
            texturePath.Resize(texturePathNode->GetValue().GetLength()+1);
            OK::MemCopy(texturePathNode->GetValue().begin(), texturePath.begin(), texturePath.GetSize());
            texturePath[texturePath.GetSize() - 1] = '\0';

            Texture& newTexture = m_Textures.Grow();
            if (newTexture.Load(renderingContext, textureName, texturePath) == EResult::Failure)
            {
                loadResult = EResult::Failure;
                break;
            }
        }
        return loadResult;
    }

    void TextureLibrary::ClearLibrary()
    {
        for (Texture& texture : m_Textures)
        {
            texture.Unload();
        }
        m_Textures.Clear();
    }

    Texture* TextureLibrary::FindTexture(const OK::char8* textureName)
    {
        auto findByName = [textureName](const Texture& texture)
        {
            return OK::MemEqual(texture.GetName().begin(), textureName, texture.GetName().GetSize());
        };
        auto foundIt = OK::FindIf(m_Textures.begin(), m_Textures.end(), findByName);
        return(foundIt != m_Textures.end() ? foundIt : nullptr);
    }
}