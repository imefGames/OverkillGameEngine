#include <stdafx.h>
#include <graphics\model\loaders\modelloaderobj.h>

#include <core\io\filereader.h>
#include <graphics\model\vertexdata.h>

namespace OK
{
    EResult ModelLoaderObj::LoadModel(const StringView& path, Array<VertexData>& vertexData, Array<OK::u32>& indexData)
    {
        String pathString{ path.begin(), path.GetLength() };
        FileReader fileReader{ pathString.begin() };

        OK::u32 vertexCount{ 0 };
        vertexData.Clear();
        indexData.Clear();

        Array<OK::Vec4> vertice;
        Array<OK::Vec4> textureCoords;
        Array<OK::Vec4> normals;

        String currentLine;
        Array<StringView> subStrings;
        Array<StringView> faceStrings;
        while (!fileReader.IsAtEOF())
        {
            fileReader.ReadLine(currentLine);
            OK::Split(currentLine, subStrings, ' ');
            if (!subStrings.IsEmpty())
            {
                const StringView& firstSubString{ subStrings[0] };
                if (firstSubString == "v")
                {
                    okAssert(subStrings.GetSize() == 4, "Invalid vertex position line.");
                    OK::f32 x{ OK::ConvertFromString<OK::f32>(subStrings[1].begin(), subStrings[1].GetLength()) };
                    OK::f32 y{ OK::ConvertFromString<OK::f32>(subStrings[2].begin(), subStrings[2].GetLength()) };
                    OK::f32 z{ OK::ConvertFromString<OK::f32>(subStrings[3].begin(), subStrings[3].GetLength()) };
                    vertice.Add(OK::Vec4{ x, y, z });
                }
                else if (firstSubString == "vt")
                {
                    okAssert(subStrings.GetSize() == 3, "Invalid vertex texture line.");
                    OK::f32 u{ OK::ConvertFromString<OK::f32>(subStrings[1].begin(), subStrings[1].GetLength()) };
                    OK::f32 v{ OK::ConvertFromString<OK::f32>(subStrings[2].begin(), subStrings[2].GetLength()) };
                    textureCoords.Add(OK::Vec4{ u, v });
                }
                else if (firstSubString == "vn")
                {
                    okAssert(subStrings.GetSize() == 4, "Invalid vertex normal line.");
                    OK::f32 x{ OK::ConvertFromString<OK::f32>(subStrings[1].begin(), subStrings[1].GetLength()) };
                    OK::f32 y{ OK::ConvertFromString<OK::f32>(subStrings[2].begin(), subStrings[2].GetLength()) };
                    OK::f32 z{ OK::ConvertFromString<OK::f32>(subStrings[3].begin(), subStrings[3].GetLength()) };
                    normals.Add(OK::Vec4{ x, y, z });
                }
                else if (firstSubString == "f")
                {
                    okAssert(subStrings.GetSize() == 4, "Invalid face line.");
                    for (OK::u32 i = 1; i < subStrings.GetSize(); ++i)
                    {
                        OK::Split(subStrings[i], faceStrings, '/');
                        okAssert(faceStrings.GetSize() == 3, "Invalid face sub part.");
                        OK::u32 vertexIndex{        OK::ConvertFromString<OK::u32>(faceStrings[0].begin(), faceStrings[0].GetLength()) - 1 };
                        OK::u32 textureCoordIndex{  OK::ConvertFromString<OK::u32>(faceStrings[1].begin(), faceStrings[1].GetLength()) - 1 };
                        OK::u32 normalIndex{        OK::ConvertFromString<OK::u32>(faceStrings[2].begin(), faceStrings[1].GetLength()) - 1 };

                        VertexData& newVertexData{ vertexData.Grow() };
                        newVertexData.m_Position = vertice[vertexIndex];
                        newVertexData.m_TextureCoords = textureCoords[textureCoordIndex];
                        newVertexData.m_Normal = normals[normalIndex];
                        newVertexData.m_Color = OK::Vec4(1.f, 1.f, 1.f, 1.f);
                        indexData.Add(vertexCount++);
                    }
                }
            }
        }

        return EResult::Success;
    }
}