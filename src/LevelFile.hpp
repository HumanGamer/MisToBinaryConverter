#pragma once

#include <platform/types.h>
#include "Mission.hpp"

class LevelFile
{
public:
    LevelFile();
    ~LevelFile();

    bool Load(const char* filename);
    bool Save(const char* filename);

    void SetMission(Mission* mission) { mMission = mission; }
    Mission* GetMission() { return mMission; }

private:
    Mission* mMission;
};