#include <stdafx.h>
#include <core\io\filereader.h>

#include <iostream>
#include <fstream>

namespace OK
{
    FileReader::FileReader(const OK::char8* filePath)
        : m_FilePath{ filePath }
    {
        fopen_s(&m_FileHandle, filePath, "rb");
    }

    FileReader::~FileReader()
    {
        if (IsFileOpen())
        {
            fclose(m_FileHandle);
        }
    }

    OK::u32 FileReader::GetFileSize() const
    {
        OK::u32 fileSize = 0;
        if (IsFileOpen())
        {
            OK::u32 fileCurrentPosition = ftell(m_FileHandle);
            fseek(m_FileHandle, 0, SEEK_END);
            fileSize = ftell(m_FileHandle);
            fseek(m_FileHandle, fileCurrentPosition, SEEK_SET);
        }
        return fileSize;
    }

    EResult FileReader::ReadFullFile(String& fileText) const
    {
        EResult readResult{ EResult::Failure };
        if (IsFileOpen())
        {
            OK::u32 fileSize = GetFileSize();
            fileText.Resize(fileSize);
            fread_s(fileText.begin(), fileSize, sizeof(OK::char8), fileSize, m_FileHandle);
            readResult = EResult::Success;
        }
        return readResult;
    }
}