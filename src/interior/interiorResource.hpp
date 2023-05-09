#pragma once

#include <platform/types.h>
#include <vector>
#include "interior.hpp"

class InteriorResource
{
public:
    InteriorResource();
    ~InteriorResource();

    bool Load(const std::string& filename);
    bool Save(const std::string& filename);

private:
    static const U32 smFileVersion;
    std::vector<Interior*> mDetailLevels;
};