#pragma once

namespace OK
{
    class JSONNode
    {
    public:
        enum ENodeType
        {
            Undefined,
            Object,
            Array,
            Leaf
        };

        JSONNode() = default;
        JSONNode(const StringView& nodeKey, const StringView& nodeData);

        const StringView& GetKey() const { return m_NodeKey; }
        const StringView& GetData() const { return m_NodeData; }

        EResult ComputeSubNodes();
        JSONNode* GetNode(const OK::char8* nodeKey);

    private:
        StringView m_NodeKey;
        StringView m_NodeData;
        ENodeType m_NodeType;
        OK::Array<JSONNode> m_SubNodes;
    };
}