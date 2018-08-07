#pragma once

namespace OK
{
    class JSONNode
    {
    public:
        enum class ENodeType
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
        ENodeType GetNodeType() const { return m_NodeType; }
        OK::u32 GetArrayNodeSize() const { return m_SubNodes.GetSize(); }

        EResult ComputeSubNodes();
        JSONNode* GetNodeAtIndex(OK::u32 nodeIndex);
        JSONNode* GetNode(const OK::char8* nodeKey);

        template<typename T>
        T GetValue(const OK::char8* nodeKey)
        {
            JSONNode* foundNode = GetNode(nodeKey);
            okAssert(foundNode != nullptr, "Could nout find Sub Node.");
            return OK::ConvertFromString<T>(foundNode->m_NodeData.begin(), foundNode->m_NodeData.GetLength());
        }

    private:
        StringView m_NodeKey;
        StringView m_NodeData;
        ENodeType m_NodeType;
        OK::Array<JSONNode> m_SubNodes;
    };
}