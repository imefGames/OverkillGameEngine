#pragma once

namespace OK
{
    class FileReader
    {
    public:
        FileReader(const OK::char8* fileName);
        ~FileReader();

    private:
        String m_FileName;
    };
}