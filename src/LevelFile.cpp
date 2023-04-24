#include "LevelFile.hpp"
#include "FileStream.hpp"

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

    file.WriteString("MBLV");
    file.Write<uint32_t>(0); // version



    return true;
}