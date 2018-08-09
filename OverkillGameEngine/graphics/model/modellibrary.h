#pragma once

namespace OK
{
    class JSONNode;
    struct RenderingContext;
    struct VertexList;

    class ModelLibrary
    {
    public:
        EResult RegisterModels(const RenderingContext& renderingContext, JSONNode* modelLibraryNode);
        void ClearLibrary();
        VertexList* FindModel(const OK::char8* modelName);

    private:
        struct ModelLibraryEntry
        {
            String m_Name;
            VertexList* m_Model = nullptr;
        };

        Array<ModelLibraryEntry> m_Models;
    };
}