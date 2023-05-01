#include "LevelFile.hpp"
#include "FileStream.hpp"

LevelFile::LevelFile()
{

}

LevelFile::~LevelFile()
{

}

bool LevelFile::Load(const char *filename)
{
    return false;
}

bool LevelFile::Save(const char *filename)
{
    FileStream file;
    if (!file.Open(filename, FileStream::OpenMode_Write))
        return false;

    file.WriteString("MBLV");
    file.Write<uint32_t>(0); // global version

    file.WriteCString("ultra"); // game string to determine which game this level is for in case special features are needed
    file.Write<uint32_t>(0); // ultra version

    // mission info
    file.WriteLocalizedString(mMission->info.name);
    file.WriteLocalizedString(mMission->info.description);
    file.WriteLocalizedString(mMission->info.startHelpText);

    file.Write(mMission->info.guid);

    file.WriteCString(mMission->info.type);
    file.WriteCString(mMission->info.artist);
    file.WriteCString(mMission->info.gameMode);
    file.WriteCString(mMission->info.sky);

    file.Write(mMission->info.levelIndex);
    file.Write(mMission->info.includeInLevelList);
    file.Write(mMission->info.difficulty);

    file.Write(mMission->info.multiplayer);
    if (mMission->info.multiplayer)
    {
        file.Write(mMission->info.timeLimit);
        file.Write(mMission->info.parGoal.score);
        file.Write(mMission->info.goldGoal.score);
        file.Write(mMission->info.numGems);
        file.Write(mMission->info.gemGroupRadius);
        file.Write(mMission->info.maxGemsPerGroup);
    } else {
        file.Write(mMission->info.parGoal.time);
        file.Write(mMission->info.goldGoal.time);
    }

    // TODO: Write rest of mission data

    return true;
}