#include "interior.hpp"

const U32 Interior::smFileVersion = 14;

Interior::Interior()
{

}

Interior::~Interior()
{

}

bool Interior::Load(Stream &stream)
{
    U32 fileVersion;
    stream.Read(&fileVersion);

    mFileVersion = fileVersion;

    if (fileVersion > smFileVersion)
    {
        printf("ERROR: Incompatible file version found.\n");
        return false;
    }

    stream.Read(&mDetailLevel);
    stream.Read(&mMinPixels);

    // TODO: Finish Implementing Interior::Load

    return true;
}

bool Interior::Save(Stream &stream)
{
    return false;
}
