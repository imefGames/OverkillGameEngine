#pragma once

#include <core\io\filereader.h>

namespace OK
{
    class JSONNode;

    class JSONParser
    {
    public:
        JSONParser(const OK::char8* filePath);
        ~JSONParser();

        EResult ParseRootNodes();
        JSONNode* GetNode(const OK::char8* nodeKey);

    private:
        FileReader m_FileReader;
        JSONNode* m_RootNode;
        String m_FileText;
    };
}