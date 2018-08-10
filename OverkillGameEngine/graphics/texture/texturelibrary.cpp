#include <stdafx.h>
#include <graphics\texture\texturelibrary.h>

#include <core\io\parsers\json\jsonnode.h>

namespace OK
{
    EResult TextureLibrary::RegisterTextures(const RenderingContext& renderingContext, JSONNode* textureLibraryNode)
    {
        EResult loadResult{ EResult::Success };

        JSONNode* textureListNode = textureLibraryNode->GetNode("TextureList");
        okAssert(textureListNode != nullptr, "Could not find Texture List node in game data file.");
        textureListNode->ComputeSubNodes();
        okAssert(textureListNode->GetNodeType() == JSONNode::ENodeType::Array, "Texture List node in must be of type Array.");

        OK::u32 textureCount = textureListNode->GetArrayNodeSize();
        m_Textures.Reserve(textureCount);
        for (OK::u32 i = 0; i < textureCount; ++i)
        {
            JSONNode* textureNode{ textureListNode->GetNodeAtIndex(i) };
            textureNode->ComputeSubNodes();

            JSONNode* textureNameNode = textureNode->GetNode("Name");
            JSONNode* texturePathNode = textureNode->GetNode("Path");

            String textureName;
            textureName.Resize(textureNameNode->GetData().GetLength());
            OK::MemCopy(textureNameNode->GetData().begin(), textureName.begin(), textureName.GetSize());

            String texturePath;
            texturePath.Resize(texturePathNode->GetData().GetLength());
            OK::MemCopy(texturePathNode->GetData().begin(), texturePath.begin(), texturePath.GetSize());

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