#include "LevelFile.hpp"

#include <fstream>

LevelFile::LevelFile()
{

}

LevelFile::~LevelFile()
{

}

bool LevelFile::load(const char *filename)
{
    return false;
}

bool LevelFile::save(const char *filename)
{
    std::fstream file;
    file.open(filename, std::ios::out | std::ios::binary);

    if (file.fail())
        return false;

    file.write("MBLV", 4);

    int version = 0;
    file.write((char*)&version, 4);

    file.flush();
    file.close();

    return true;
}