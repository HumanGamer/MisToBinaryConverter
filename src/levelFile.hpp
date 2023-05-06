#pragma once

#include <platform/types.h>
#include <core/streams/stream.hpp>
#include <mission/mission.hpp>
#include <interior/interiorResource.hpp>

class LevelFile
{
public:
    LevelFile();
    ~LevelFile();

    bool Load(const char* filename);
    bool Save(const char* filename);

    void SetMission(Mission* mission) { mMission = mission; }
    Mission* GetMission() { return mMission; }

    void SetInteriors(const std::vector<InteriorResource*>& interiors) { mInteriors = interiors; }

protected:
    enum CompressionFlags
    {
        NoCompression = 0,
        ZlibCompression = 1,
        ValueCompression = 2
    };

private:
    Mission* mMission;
    std::vector<InteriorResource*> mInteriors;
};