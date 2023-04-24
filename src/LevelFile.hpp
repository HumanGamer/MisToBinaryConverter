#pragma once

#include <platform/types.h>
#include "Mission.hpp"

class LevelFile
{
public:
    LevelFile();
    ~LevelFile();

    bool load(const char* filename);
    bool save(const char* filename);

    void setMission(Mission* mission) { mMission = mission; }
    Mission* getMission() { return mMission; }

private:
    Mission* mMission;
};