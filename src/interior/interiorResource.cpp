#include "interiorResource.hpp"
#include <core/streams/fileStream.hpp>

const U32 InteriorResource::smFileVersion = 44;

InteriorResource::InteriorResource()
{

}

InteriorResource::~InteriorResource()
{

}

bool InteriorResource::Load(const std::string &filename)
{
    FileStream file;
    if (!file.Open(filename, FileStream::OpenMode_Read))
        return false;

    file.DisableCompression();

    U32 fileVersion;
    file.Read(&fileVersion);
    if (fileVersion != smFileVersion)
    {
        printf("ERROR: File version mismatch in '%s'.\n", filename.c_str());
        return false;
    }

    bool previewIncluded;
    file.Read(&previewIncluded);
    if (previewIncluded)
    {
        printf("ERROR: Previews included in '%s' but not supported yet.\n", filename.c_str());
        return false;
    }

    U32 numDetailLevels;
    file.Read(&numDetailLevels);
    mDetailLevels.resize(numDetailLevels);
    for (U32 i = 0; i < numDetailLevels; ++i)
    {
        mDetailLevels[i] = new Interior();
        if (!mDetailLevels[i]->Load(file))
        {
            printf("ERROR: Failed to load detail level %d in '%s'.\n", i, filename.c_str());
            return false;
        }
    }

    // TODO: Read SubObjects

    // TODO: Read Triggers

    // TODO: Read InteriorPathFollowers

    // TODO: Read ForceFields

    // TODO: Read AISpecialNodes

    // TODO: Read VehicleCollisions

    // TODO: Read GameEntities

    return true;
}

bool InteriorResource::Save(const std::string &filename)
{
    // TODO: Implement InteriorResource::Save

    return true;
}
