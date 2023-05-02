#include "LevelFile.hpp"
#include <core/streams/MemStream.hpp>
#include <core/streams/FileStream.hpp>

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

    // TODO: Maybe use a string table for strings?

    MemStream memStream;
    {
        // mission info
        memStream.WriteLocalizedString(mMission->info.name);
        memStream.WriteLocalizedString(mMission->info.description);
        memStream.WriteLocalizedString(mMission->info.startHelpText);

        memStream.Write(mMission->info.guid);

        memStream.WriteCString(mMission->info.type);
        memStream.WriteCString(mMission->info.artist);
        memStream.WriteCString(mMission->info.gameMode);
        memStream.WriteCString(mMission->info.sky);

        memStream.Write7BitEncodedInt(mMission->info.levelIndex);
        memStream.Write(mMission->info.includeInLevelList);
        memStream.Write7BitEncodedInt(mMission->info.difficulty);

        memStream.Write(mMission->info.multiplayer);
        if (mMission->info.multiplayer)
        {
            memStream.Write7BitEncodedInt(mMission->info.timeLimit);
            memStream.Write7BitEncodedInt(mMission->info.parGoal.score);
            memStream.Write7BitEncodedInt(mMission->info.goldGoal.score);
            memStream.Write7BitEncodedInt(mMission->info.numGems);
            memStream.Write7BitEncodedInt(mMission->info.gemGroupRadius);
            memStream.Write7BitEncodedInt(mMission->info.maxGemsPerGroup);
        } else
        {
            memStream.Write7BitEncodedInt(mMission->info.parGoal.time);
            memStream.Write7BitEncodedInt(mMission->info.goldGoal.time);
        }

        // Shapes
        memStream.Write7BitEncodedInt((U32)mMission->shapes.size());
        for (auto &shape: mMission->shapes)
        {
            memStream.WriteCString(shape.type);
            //memStream.WriteCString(shape.name);
            memStream.Write(shape.position);
            memStream.Write(shape.rotation);
            memStream.Write(shape.scale);
        }

        // Items
        memStream.Write7BitEncodedInt((U32)mMission->items.size());
        for (auto &item: mMission->items)
        {
            memStream.WriteCString(item.type);
            //memStream.WriteCString(item.name);
            memStream.Write(item.position);
            memStream.Write(item.rotation);
            memStream.Write(item.scale);
            memStream.Write(item.rotate);
        }

        // Geometry
        memStream.Write7BitEncodedInt((U32)mMission->geometries.size());
        for (auto &geometry: mMission->geometries)
        {
            memStream.WriteCString(geometry.type);
            //memStream.WriteCString(geometry.name);
            memStream.Write(geometry.position);
            memStream.Write(geometry.rotation);
            memStream.Write(geometry.scale);

            // TODO: Support embedded geometry
            memStream.WriteCString(geometry.path);
        }

        // Moving Geometry
        memStream.Write7BitEncodedInt((U32)mMission->movingGeometries.size());
        for (auto &movingGeometry: mMission->movingGeometries)
        {
            memStream.WriteCString(movingGeometry.type);
            memStream.WriteCString(movingGeometry.subtype);
            //memStream.WriteCString(movingGeometry.name);
            memStream.Write(movingGeometry.position);
            memStream.Write(movingGeometry.rotation);
            memStream.Write(movingGeometry.scale);
            memStream.Write7BitEncodedInt(movingGeometry.initialTargetPosition);
            memStream.Write7BitEncodedInt(movingGeometry.initialPosition);
            memStream.Write(movingGeometry.looping);

            // TODO: Support embedded geometry
            memStream.WriteCString(movingGeometry.path);
            memStream.Write7BitEncodedInt(movingGeometry.indexInFile);

            memStream.Write(movingGeometry.triggered);
            if (movingGeometry.triggered)
            {
                memStream.WriteCString(movingGeometry.trigger.type);
                memStream.Write(movingGeometry.trigger.position);
                memStream.Write(movingGeometry.trigger.rotation);
                memStream.Write(movingGeometry.trigger.scale);
                memStream.Write(movingGeometry.trigger.polyhedron);
                memStream.Write7BitEncodedInt(movingGeometry.trigger.targetTime);
            }

            // Moving Geometry Keyframes
            memStream.Write7BitEncodedInt((U32)movingGeometry.keyframes.size());
            for (auto &keyframe: movingGeometry.keyframes)
            {
                memStream.Write(keyframe.position);
                memStream.Write(keyframe.rotation);
                memStream.Write(keyframe.scale);
                memStream.Write7BitEncodedInt(keyframe.seqNum);
                memStream.WriteCString(keyframe.type);
                memStream.Write7BitEncodedInt(keyframe.msToNext);
                memStream.WriteCString(keyframe.smoothingType);
            }
        }

        // Spawn Points
        memStream.Write7BitEncodedInt((U32)mMission->spawnPoints.size());
        for (auto &spawnPoint: mMission->spawnPoints)
        {
            memStream.WriteCString(spawnPoint.className);
            memStream.WriteCString(spawnPoint.type);
            //memStream.WriteCString(spawnPoint.name);
            memStream.Write(spawnPoint.position);
            memStream.Write(spawnPoint.rotation);
            memStream.Write(spawnPoint.scale);
        }

        // Help Triggers
        memStream.Write7BitEncodedInt((U32)mMission->helpTriggers.size());
        for (auto &helpTrigger: mMission->helpTriggers)
        {
            memStream.Write(helpTrigger.position);
            memStream.Write(helpTrigger.rotation);
            memStream.Write(helpTrigger.scale);
            memStream.Write(helpTrigger.polyhedron);
            memStream.WriteLocalizedString(helpTrigger.msg);
        }

        // Bounds Triggers
        memStream.Write7BitEncodedInt((U32)mMission->boundsTriggers.size());
        for (auto &boundsTrigger: mMission->boundsTriggers)
        {
            memStream.Write(boundsTrigger.position);
            memStream.Write(boundsTrigger.rotation);
            memStream.Write(boundsTrigger.scale);
            memStream.Write(boundsTrigger.polyhedron);
            memStream.Write(boundsTrigger.inBounds);
        }

        // Checkpoints
        memStream.Write7BitEncodedInt((U32)mMission->checkpoints.size());
        for (auto &checkpoint: mMission->checkpoints)
        {
            memStream.Write(checkpoint.position);
            memStream.Write(checkpoint.rotation);
            memStream.Write(checkpoint.scale);
            memStream.Write7BitEncodedInt(checkpoint.sequence);

            // Checkpoint Trigger
            memStream.Write(checkpoint.trigger.position);
            memStream.Write(checkpoint.trigger.rotation);
            memStream.Write(checkpoint.trigger.scale);
            memStream.Write(checkpoint.trigger.polyhedron);
        }

        // Gem Spawns
        memStream.Write7BitEncodedInt((U32)mMission->gemSpawns.size());
        for (auto &gemSpawn: mMission->gemSpawns)
        {
            memStream.WriteCString(gemSpawn.type);
            memStream.Write(gemSpawn.position);
            memStream.Write(gemSpawn.rotation);
            memStream.Write(gemSpawn.scale);
        }

        // Preview Camera
        memStream.Write(mMission->previewCamera.position);
        memStream.Write(mMission->previewCamera.rotation);
    }
    U8* missionBytes = memStream.GetBytes();
    size_t missionSize = memStream.GetSize();

    // Write the mission size to allow skipping the mission when reading
    file.Write7BitEncodedInt((U32)missionSize);

    // Write the mission file
    file.WriteBytes((char*)missionBytes, missionSize);

    return true;
}