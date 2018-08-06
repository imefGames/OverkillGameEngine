#include <stdafx.h>
#include <core\io\parsers\json\jsonnode.h>

namespace OK
{
    JSONNode::JSONNode(const StringView& nodeKey, const StringView& nodeData)
        : m_NodeKey{ nodeKey }
        , m_NodeData{ nodeData }
    {
    }

    EResult JSONNode::ComputeSubNodes()
    {
        //TODO: parse data tp find sub nodes.
        return EResult::Failure;
    }

    JSONNode* JSONNode::GetNode(const OK::char8* nodeKey)
    {
        auto findByKey = [nodeKey](JSONNode& node)
        {
            return OK::MemEqual(node.GetKey().begin(), nodeKey, node.GetKey().GetLength());
        };

        auto foundIt = OK::FindIf(m_SubNodes.begin(), m_SubNodes.end(), findByKey);
        return (foundIt != m_SubNodes.end() ? foundIt : nullptr);
    }
}