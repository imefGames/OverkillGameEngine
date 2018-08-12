#include <stdafx.h>
#include <core\io\parsers\json\jsonnode.h>

namespace OK
{
    const JSONNode& JSONNode::operator[](unsigned int index) const
    {
        okAssert(m_NodeType == ENodeType::Array, "JSon node must be of type Array.");
        okAssert(index < m_SubNodes.GetSize(), "Index too high for array JSon node.");
        return m_SubNodes[index];
    }

    const JSONNode* JSONNode::operator[](const char* nodeName) const
    {
        okAssert(m_NodeType == ENodeType::Object, "JSon node must be of type Object.");
        auto findByName = [nodeName](const auto& node)
        {
            return node.m_Name == nodeName;
        };
        auto foundIt = FindIf(m_SubNodes.begin(), m_SubNodes.end(), findByName);
        return &(*foundIt);
    }

    const StringView& JSONNode::GetValue() const
    {
        okAssert(m_NodeType == ENodeType::Leaf, "JSon node must be of type Leaf.");
        return m_Value;
    }

    JSONNode::const_iterator JSONNode::begin() const
    {
        okAssert(m_NodeType == ENodeType::Array, "JSon node must be of type Array.");
        return &(*m_SubNodes.begin());
    }

    JSONNode::const_iterator JSONNode::end() const
    {
        okAssert(m_NodeType == ENodeType::Array, "JSon node must be of type Array.");
        return &(*m_SubNodes.end());
    }
}