#include <stdafx.h>
#include <graphics\model\modellibrary.h>

#include <core\io\parsers\json\jsonnode.h>
#include <graphics\model\vertexlist.h>
#include <graphics\model\loaders\modelloaderobj.h>
#include <graphics\shaders\shader.h>

namespace OK
{
    EResult ModelLibrary::RegisterModels(const RenderingContext& renderingContext, const JSONNode& modelLibraryNode)
    {
        EResult loadResult{ EResult::Success };
        Array<VertexData> vertexData;
        Array<OK::u32> indexData;

        const JSONNode* modelListNode = modelLibraryNode["ModelList"];
        m_Models.Clear();
        m_Models.Reserve(modelListNode->GetSubNodeCount() + 1);
        RegisterSpriteModel(renderingContext);
        for (const JSONNode& modelNode : *modelListNode)
        {
            ModelLibraryEntry& newModel{ m_Models.Grow() };
            const JSONNode* modelName = modelNode["Name"];
            newModel.m_Name.Resize(modelName->GetValue().GetLength());
            OK::MemCopy(modelName->GetValue().begin(), newModel.m_Name.begin(), newModel.m_Name.GetSize());

            const StringView& filePath{ modelNode["Path"]->GetValue() };
            if (ModelLoaderObj::LoadModel(filePath, vertexData, indexData) == EResult::Success)
            {
                newModel.m_Model = new VertexList;
                newModel.m_Model->SetVertexList(renderingContext, vertexData);
                newModel.m_Model->SetIndexList(renderingContext, indexData);
            }
            else
            {
                loadResult = EResult::Failure;
                break;
            }
        }

        return loadResult;
    }

    void ModelLibrary::ClearLibrary()
    {
        for (ModelLibraryEntry& modelEntry : m_Models)
        {
            okSafeDelete(modelEntry.m_Model);
        }
        m_Models.Clear();
    }

    VertexList* ModelLibrary::FindModel(const OK::char8* modelName)
    {
        auto findByName = [modelName](const ModelLibraryEntry& modelEntry)
        {
            return OK::MemEqual(modelEntry.m_Name.begin(), modelName, modelEntry.m_Name.GetSize());
        };
        auto foundIt = OK::FindIf(m_Models.begin(), m_Models.end(), findByName);
        return(foundIt != m_Models.end() ? foundIt->m_Model : nullptr);
    }

    void ModelLibrary::RegisterSpriteModel(const RenderingContext& renderingContext)
    {
        ModelLibraryEntry& newModel{ m_Models.Grow() };
        newModel.m_Name = String("Sprite");

        Array<VertexData> vertexData;
        vertexData.Add(VertexData{ OK::Vec4{ -0.5f, -0.5f }, OK::Vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, OK::Vec4{ 0.0f, 0.0f }, OK::Vec4{0.0f, 0.0f, -1.0f} });
        vertexData.Add(VertexData{ OK::Vec4{  0.5f,  0.5f }, OK::Vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, OK::Vec4{ 1.0f, 1.0f }, OK::Vec4{0.0f, 0.0f, -1.0f} });
        vertexData.Add(VertexData{ OK::Vec4{ -0.5f,  0.5f }, OK::Vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, OK::Vec4{ 0.0f, 1.0f }, OK::Vec4{0.0f, 0.0f, -1.0f} });
        vertexData.Add(VertexData{ OK::Vec4{  0.5f, -0.5f }, OK::Vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, OK::Vec4{ 1.0f, 0.0f }, OK::Vec4{0.0f, 0.0f, -1.0f} });

        Array<OK::u32> indexData;
        indexData.Add(0);
        indexData.Add(2);
        indexData.Add(1);
        indexData.Add(0);
        indexData.Add(1);
        indexData.Add(3);

        newModel.m_Model = new VertexList;
        newModel.m_Model->SetVertexList(renderingContext, vertexData);
        newModel.m_Model->SetIndexList(renderingContext, indexData);
    }
}