#pragma once

namespace OK
{
    class JSONNode
    {
    public:
        JSONNode() = default;
        JSONNode(const StringView& nodeKey, const StringView& nodeData);

        const StringView& GetKey() const { return m_NodeKey; }
        const StringView& GetData() const { return m_NodeData; }

        EResult ComputeSubNodes();
        JSONNode* GetNode(const OK::char8* nodeKey);

    private:
        StringView m_NodeKey;
        StringView m_NodeData;

        Array<JSONNode> m_SubNodes;
    };
}