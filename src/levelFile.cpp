#include "levelFile.hpp"
#include <core/streams/memStream.hpp>
#include <core/streams/fileStream.hpp>
#include <core/compression.hpp>

LevelFile::LevelFile()
{

}

LevelFile::~LevelFile()
{

}

bool LevelFile::Load(const char *filename)
{
    return false;
}

bool LevelFile::Save(const char *filename)
{
    FileStream file;
    if (!file.Open(filename, FileStream::OpenMode_Write))
        return false;

    bool zlibCompression = true;
    bool valueCompression = true;

    U8 flags = NoCompression;
    if (zlibCompression)
        flags |= ZlibCompression;
    if (valueCompression)
        flags |= ValueCompression;

    file.DisableCompression();
    {
        // Header

        file.WriteString("MBLV");
        file.Write<U32>(0); // global version

        // game string to determine which game this level is for.
        // this is so that other MB games can use the same level format,
        // and still have their own versioning.
        file.WriteCString("ultra");
        file.Write<U32>(0); // ultra version

        file.Write(flags);
    }

    if (valueCompression)
        file.EnableCompression();

    mMission->write(file, zlibCompression, valueCompression);

    return true;
}
