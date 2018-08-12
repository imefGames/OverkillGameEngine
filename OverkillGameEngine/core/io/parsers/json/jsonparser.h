#pragma once

namespace OK
{
    class JSONNode;

    class JSONParser
    {
    public:
        void Parse(String::const_iterator searchStart, String::const_iterator searchEnd, JSONNode& result);

    private:
        void ParseInternal(String::const_iterator& searchStart, String::const_iterator searchEnd, JSONNode& result, const JSONNode* parent);
        static void FindNextToken(String::const_iterator searchStart, String::const_iterator searchEnd, String::const_iterator& nextSearchStart, StringView& foundToken);
        static void SkipSpaces(String::const_iterator& searchStart, String::const_iterator searchEnd);
        static void SkipUntil(String::const_iterator& searchStart, String::const_iterator searchEnd, char endChar);
    };
}