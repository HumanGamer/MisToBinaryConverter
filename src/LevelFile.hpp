#pragma once

#include <platform/types.h>
#include <core/streams/Stream.hpp>
#include <mission/Mission.hpp>

class LevelFile
{
public:
    LevelFile();
    ~LevelFile();

    bool Load(const char* filename);
    bool Save(const char* filename);

    void SetMission(Mission* mission) { mMission = mission; }
    Mission* GetMission() { return mMission; }

protected:
    enum CompressionFlags
    {
        NoCompression = 0,
        ZlibCompression = 1,
        ValueCompression = 2
    };

private:
    Mission* mMission;
};