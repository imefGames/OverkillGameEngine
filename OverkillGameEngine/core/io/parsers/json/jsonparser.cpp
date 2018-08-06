#include <stdafx.h>
#include <core\io\parsers\json\jsonparser.h>

#include <core\io\parsers\json\jsonnode.h>

namespace OK
{
    JSONParser::JSONParser(const OK::char8* filePath)
        : m_FileReader{ filePath }
        , m_RootNode{ nullptr }
    {
    }

    JSONParser::~JSONParser()
    {
        okSafeDelete(m_RootNode);
    }

    EResult JSONParser::ParseRootNodes()
    {
        EResult parseResult = EResult::Failure;
        okSafeDelete(m_RootNode);
        if (m_RootNode == nullptr)
        {
            parseResult = m_FileReader.ReadFullFile(m_FileText);
            if (parseResult == EResult::Success)
            {
                StringView nodeKey;
                StringView nodeData{ m_FileText.begin(), m_FileText.GetSize() };
                m_RootNode = new JSONNode(nodeKey, nodeData);
                parseResult = m_RootNode->ComputeSubNodes();
            }
        }
        return parseResult;
    }

    JSONNode* JSONParser::GetNode(const OK::char8* nodeKey)
    {
        return (m_RootNode != nullptr ? m_RootNode->GetNode(nodeKey) : nullptr);
    }
}