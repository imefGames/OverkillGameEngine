#include <stdafx.h>
#include <core\io\filereader.h>

namespace OK
{
    FileReader::FileReader(const OK::char8* fileName)
        : m_FileName{ fileName }
    {
    }

    FileReader::~FileReader()
    {
    }
}