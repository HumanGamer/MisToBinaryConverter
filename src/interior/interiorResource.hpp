#pragma once

#include <platform/types.h>

class InteriorResource
{
public:
    InteriorResource();
    ~InteriorResource();

    bool Load(const std::string& filename);
    bool Save(const std::string& filename);

protected:

};