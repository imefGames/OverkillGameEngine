#pragma once

#include <core\string.h>
#include <core\containers\array.h>

namespace OK
{
    class JSONNode
    {
    public:
        using const_iterator = const JSONNode*;

        const JSONNode& operator[](unsigned int index) const;
        const JSONNode* operator[](const char* nodeName) const;
        const StringView& GetValue() const;

        OK::u32 GetSubNodeCount() const { return m_SubNodes.GetSize(); }

        const_iterator begin() const;
        const_iterator end() const;

        template<typename T>
        T GetValueAs() const
        {
            const StringView& value{ GetValue() };
            return ConvertFromString<T>(value.begin(), value.GetLength());
        }

        template<typename T>
        T GetValueAs(const char* nodeName) const
        {
            const JSONNode* foundNode{ (*this)[nodeName] };
            okAssert(foundNode != nullptr, "Could not find node.");
            return foundNode->GetValueAs<T>();
        }

        template<typename T>
        T GetValueAs(const char* nodeName, T fallback) const
        {
            const JSONNode* foundNode{ (*this)[nodeName] };
            return (foundNode != nullptr ? foundNode->GetValueAs<T>() : fallback);
        }

    private:
        enum class ENodeType
        {
            Undefined,
            Object,
            Array,
            Leaf
        };

        StringView m_Name;
        StringView m_Value;
        Array<JSONNode> m_SubNodes;
        ENodeType m_NodeType{ ENodeType::Undefined };

        friend class JSONParser;
    };
}