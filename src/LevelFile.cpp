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

    // TODO: Use a string table for strings

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

    // Shapes
    file.Write<uint32_t>(mMission->shapes.size());
    for (auto& shape : mMission->shapes)
    {
        file.WriteCString(shape.type);
        //file.WriteCString(shape.name);
        file.Write(shape.position);
        file.Write(shape.rotation);
        file.Write(shape.scale);
    }

    // Items
    file.Write<uint32_t>(mMission->items.size());
    for (auto& item : mMission->items)
    {
        file.WriteCString(item.type);
        //file.WriteCString(item.name);
        file.Write(item.position);
        file.Write(item.rotation);
        file.Write(item.scale);
        file.Write(item.rotate);
    }

    // Geometry
    file.Write<uint32_t>(mMission->geometries.size());
    for (auto& geometry : mMission->geometries)
    {
        file.WriteCString(geometry.type);
        //file.WriteCString(geometry.name);
        file.Write(geometry.position);
        file.Write(geometry.rotation);
        file.Write(geometry.scale);

        // TODO: Support embedded geometry
        file.WriteCString(geometry.path);
    }

    // Moving Geometry
    file.Write<uint32_t>(mMission->movingGeometries.size());
    for (auto& movingGeometry : mMission->movingGeometries)
    {
        file.WriteCString(movingGeometry.type);
        file.WriteCString(movingGeometry.subtype);
        //file.WriteCString(movingGeometry.name);
        file.Write(movingGeometry.position);
        file.Write(movingGeometry.rotation);
        file.Write(movingGeometry.scale);
        file.Write(movingGeometry.initialTargetPosition);
        file.Write(movingGeometry.initialPosition);
        file.Write(movingGeometry.looping);

        // TODO: Support embedded geometry
        file.WriteCString(movingGeometry.path);
        file.Write(movingGeometry.indexInFile);

        file.Write(movingGeometry.triggered);
        if (movingGeometry.triggered)
        {
            file.WriteCString(movingGeometry.trigger.type);
            file.Write(movingGeometry.trigger.position);
            file.Write(movingGeometry.trigger.rotation);
            file.Write(movingGeometry.trigger.scale);

            // TODO: Maybe do this without strings?
            file.WriteCString(movingGeometry.trigger.polyhedron);

            file.Write(movingGeometry.trigger.targetTime);
        }

        // Moving Geometry Keyframes
        file.Write<uint32_t>(movingGeometry.keyframes.size());
        for (auto& keyframe : movingGeometry.keyframes)
        {
            file.Write(keyframe.position);
            file.Write(keyframe.rotation);
            file.Write(keyframe.scale);
            file.Write(keyframe.seqNum);
            file.WriteCString(keyframe.type);
            file.Write(keyframe.msToNext);
            file.WriteCString(keyframe.smoothingType);
        }
    }

    // Spawn Points
    file.Write<uint32_t>(mMission->spawnPoints.size());
    for (auto& spawnPoint : mMission->spawnPoints)
    {
        file.WriteCString(spawnPoint.className);
        file.WriteCString(spawnPoint.type);
        //file.WriteCString(spawnPoint.name);
        file.Write(spawnPoint.position);
        file.Write(spawnPoint.rotation);
        file.Write(spawnPoint.scale);
    }

    // Help Triggers
    file.Write<uint32_t>(mMission->helpTriggers.size());
    for (auto& helpTrigger : mMission->helpTriggers)
    {
        file.Write(helpTrigger.position);
        file.Write(helpTrigger.rotation);
        file.Write(helpTrigger.scale);

        // TODO: Maybe do this without strings?
        file.WriteCString(helpTrigger.polyhedron);

        file.WriteLocalizedString(helpTrigger.msg);
    }

    // Bounds Triggers
    file.Write<uint32_t>(mMission->boundsTriggers.size());
    for (auto& boundsTrigger : mMission->boundsTriggers)
    {
        file.Write(boundsTrigger.position);
        file.Write(boundsTrigger.rotation);
        file.Write(boundsTrigger.scale);

        // TODO: Maybe do this without strings?
        file.WriteCString(boundsTrigger.polyhedron);

        file.Write(boundsTrigger.inBounds);
    }

    // Checkpoints
    file.Write<uint32_t>(mMission->checkpoints.size());
    for (auto& checkpoint : mMission->checkpoints)
    {
        file.Write(checkpoint.position);
        file.Write(checkpoint.rotation);
        file.Write(checkpoint.scale);
        file.Write(checkpoint.sequence);

        // Checkpoint Trigger
        file.Write(checkpoint.trigger.position);
        file.Write(checkpoint.trigger.rotation);
        file.Write(checkpoint.trigger.scale);

        // TODO: Maybe do this without strings?
        file.WriteCString(checkpoint.trigger.polyhedron);
    }

    // Gem Spawns
    file.Write<uint32_t>(mMission->gemSpawns.size());
    for (auto& gemSpawn : mMission->gemSpawns)
    {
        file.WriteCString(gemSpawn.type);
        file.Write(gemSpawn.position);
        file.Write(gemSpawn.rotation);
        file.Write(gemSpawn.scale);
    }

    // Preview Camera
    file.Write(mMission->previewCamera.position);
    file.Write(mMission->previewCamera.rotation);

    return true;
}