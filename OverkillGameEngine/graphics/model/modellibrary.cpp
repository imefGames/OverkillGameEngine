#include <stdafx.h>
#include <graphics\model\modellibrary.h>

#include <core\io\parsers\json\jsonnode.h>
#include <graphics\model\vertexlist.h>
#include <graphics\shaders\shader.h>

namespace OK
{
    EResult ModelLibrary::RegisterModels(const RenderingContext& renderingContext, JSONNode* modelLibraryNode)
    {
        EResult loadResult{ EResult::Success };

        JSONNode* modelListNode = modelLibraryNode->GetNode("ModelList");
        okAssert(modelListNode != nullptr, "Could not find Model List node in game data file.");
        modelListNode->ComputeSubNodes();
        okAssert(modelListNode->GetNodeType() == JSONNode::ENodeType::Array, "Model List node in must be of type Array.");

        OK::u32 modelCount = modelListNode->GetArrayNodeSize();
        m_Models.Reserve(modelCount);
        for (OK::u32 i = 0; i < modelCount; ++i)
        {
            JSONNode* modelNode{ modelListNode->GetNodeAtIndex(i) };
            modelNode->ComputeSubNodes();
            ModelLibraryEntry& newModel{ m_Models.Grow() };
            JSONNode* modelName = modelNode->GetNode("Name");
            newModel.m_Name.Resize(modelName->GetData().GetLength());
            OK::MemCopy(modelName->GetData().begin(), newModel.m_Name.begin(), newModel.m_Name.GetSize());

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