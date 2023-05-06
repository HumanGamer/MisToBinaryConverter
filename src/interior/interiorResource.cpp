#include "interiorResource.hpp"
#include <core/streams/fileStream.hpp>

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

    // TODO: Implement InteriorResource::Load

    return true;
}

bool InteriorResource::Save(const std::string &filename)
{
    // TODO: Implement InteriorResource::Save

    return true;
}
