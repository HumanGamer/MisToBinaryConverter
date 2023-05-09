#pragma once

#include <platform/types.h>
#include <core/streams/stream.hpp>

class Interior
{
public:
    Interior();
    ~Interior();

    bool Load(Stream &stream);
    bool Save(Stream &stream);

private:
    static const U32 smFileVersion;
    U32 mFileVersion;

    U32 mDetailLevel;
    U32 mMinPixels;
};