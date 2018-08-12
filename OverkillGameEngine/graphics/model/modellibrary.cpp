#include <stdafx.h>
#include <graphics\model\modellibrary.h>

#include <core\io\parsers\json\jsonnode.h>
#include <graphics\model\vertexlist.h>
#include <graphics\shaders\shader.h>

namespace OK
{
    EResult ModelLibrary::RegisterModels(const RenderingContext& renderingContext, const JSONNode& modelLibraryNode)
    {
        EResult loadResult{ EResult::Success };

        const JSONNode* modelListNode = modelLibraryNode["ModelList"];
        m_Models.Reserve(modelListNode->GetSubNodeCount());
        for (const JSONNode& modelNode : *modelListNode)
        {
            ModelLibraryEntry& newModel{ m_Models.Grow() };
            const JSONNode* modelName = modelNode["Name"];
            newModel.m_Name.Resize(modelName->GetValue().GetLength());
            OK::MemCopy(modelName->GetValue().begin(), newModel.m_Name.begin(), newModel.m_Name.GetSize());

            newModel.m_Model = new VertexList;
            if (newModel.m_Model->LoadVertexList(renderingContext, modelNode) == EResult::Failure)
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
}