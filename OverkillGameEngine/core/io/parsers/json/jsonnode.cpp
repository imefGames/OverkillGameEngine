#include <stdafx.h>
#include <core\io\parsers\json\jsonnode.h>

#include <core\io\parsers\parserutils.h>

namespace OK
{
    JSONNode::JSONNode(const StringView& nodeKey, const StringView& nodeData)
        : m_NodeKey{ nodeKey }
        , m_NodeData{ nodeData }
        , m_NodeType{ ENodeType::Undefined }
    {
    }

    EResult JSONNode::ComputeSubNodes()
    {
        if (m_NodeType == ENodeType::Undefined)
        {
            StringView nextToken;
            if (ParserUtils::GetNextToken(m_NodeData, nextToken) == EResult::Success)
            {
                if (nextToken == "[")
                {
                    while (ParserUtils::GetNextToken(nextToken, nextToken) == EResult::Success)
                    {
                        JSONNode& newNode = m_SubNodes.Grow();
                        newNode.m_NodeType = ENodeType::Undefined;
                        if (ParserUtils::ParseUntilEndOfScope(StringView{ nextToken.end(), m_NodeData.end() }, newNode.m_NodeData, nextToken) == EResult::Success)
                        {
                            if (nextToken == "]")
                            {
                                if (ParserUtils::GetNextToken(StringView{ nextToken.end(), m_NodeData.end() }, nextToken) == EResult::Success)
                                {
                                    //TODO: report error
                                }
                                else
                                {
                                    m_NodeType = ENodeType::Array;
                                }
                            }
                            else if (nextToken != ",")
                            {
                                //TODO: report error
                            }
                        }
                    }
                }
                else if (nextToken == "{")
                {
                    while (ParserUtils::GetNextToken(StringView{ nextToken.end(), m_NodeData.end() }, nextToken) == EResult::Success)
                    {
                        JSONNode& newNode = m_SubNodes.Grow();
                        newNode.m_NodeType = ENodeType::Undefined;
                        newNode.m_NodeKey = nextToken; //TODO: check node is key
                        if (ParserUtils::GetNextToken(StringView{ nextToken.end(), m_NodeData.end() }, nextToken) == EResult::Success)
                        {
                            if (nextToken != ":")
                            {
                                //TODO: report error
                                break;
                            }
                        }

                        if (ParserUtils::ParseUntilEndOfScope(StringView{ nextToken.end(), m_NodeData.end() }, newNode.m_NodeData, nextToken) == EResult::Success)
                        {
                            if (nextToken == "}")
                            {
                                if (ParserUtils::GetNextToken(StringView{ nextToken.end(), m_NodeData.end() }, nextToken) == EResult::Success)
                                {
                                    //TODO: report error
                                    break;
                                }
                                else
                                {
                                    m_NodeType = ENodeType::Object;
                                }
                            }
                            else if (nextToken != ",")
                            {
                                //TODO: report error
                                break;
                            }
                        }
                    }
                }
                else
                {
                    m_NodeType = ENodeType::Leaf;
                }
            }
        }
        return (m_NodeType == ENodeType::Undefined ? EResult::Failure : EResult::Success);
    }

    JSONNode* JSONNode::GetNodeAtIndex(OK::u32 nodeIndex)
    {
        JSONNode* foundNode{ nullptr };
        okAssert(m_NodeType == ENodeType::Array, "JSON node must be of type array to access its index.");
        if (m_NodeType == ENodeType::Array)
        {
            foundNode = &(m_SubNodes[nodeIndex]);
        }
        return foundNode;
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