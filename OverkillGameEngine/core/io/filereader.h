#pragma once

#include <cstdio>

namespace OK
{
    class FileReader
    {
    public:
        FileReader(const OK::char8* filePath);
        ~FileReader();

        OK::Bool IsFileOpen() const { return m_FileHandle != nullptr; }
        OK::Bool IsAtEOF() const { return feof(m_FileHandle); }
        const String& GetFilePath() const { return m_FilePath; }
        OK::u32 GetFileSize() const;

        EResult ReadFullFile(String& fileText) const;
        EResult ReadLine(String& fileText);

    private:
        String m_FilePath;
        FILE* m_FileHandle;
    };
}