#include "LevelFile.hpp"
#include <core/streams/MemStream.hpp>
#include <core/streams/FileStream.hpp>
#include <core/Compression.hpp>

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
    file.RawWrite<U32>(0); // global version

    file.WriteCString("ultra"); // game string to determine which game this level is for in case special features are needed
    file.RawWrite<U32>(0); // ultra version

    MemStream wrappedMissionStream;
    {
        MemStream baseMissionStream;
        {
            // mission info
            baseMissionStream.WriteLocalizedString(mMission->info.name);
            baseMissionStream.WriteLocalizedString(mMission->info.description);
            baseMissionStream.WriteLocalizedString(mMission->info.startHelpText);

            baseMissionStream.Write(mMission->info.guid);

            baseMissionStream.WriteSTString(mMission->info.type);
            baseMissionStream.WriteSTString(mMission->info.artist);
            baseMissionStream.WriteSTString(mMission->info.gameMode);
            baseMissionStream.WriteSTString(mMission->info.sky);

            baseMissionStream.Write(mMission->info.levelIndex);
            baseMissionStream.Write(mMission->info.includeInLevelList);
            baseMissionStream.Write(mMission->info.difficulty);

            baseMissionStream.Write(mMission->info.multiplayer);
            if (mMission->info.multiplayer)
            {
                baseMissionStream.Write(mMission->info.timeLimit);
                baseMissionStream.Write(mMission->info.parGoal.score);
                baseMissionStream.Write(mMission->info.goldGoal.score);
                baseMissionStream.Write(mMission->info.numGems);
                baseMissionStream.Write(mMission->info.gemGroupRadius);
                baseMissionStream.Write(mMission->info.maxGemsPerGroup);
            } else
            {
                baseMissionStream.Write(mMission->info.parGoal.time);
                baseMissionStream.Write(mMission->info.goldGoal.time);
            }

            // Shapes
            baseMissionStream.Write<U32>(mMission->shapes.size());
            for (auto &shape: mMission->shapes)
            {
                baseMissionStream.WriteSTString(shape.type);
                //memStream.WriteSTString(shape.name);
                baseMissionStream.Write(shape.position);
                baseMissionStream.Write(shape.rotation);
                baseMissionStream.Write(shape.scale);
            }

            // Items
            baseMissionStream.Write<U32>(mMission->items.size());
            for (auto &item: mMission->items)
            {
                baseMissionStream.WriteSTString(item.type);
                //memStream.WriteCString(item.name);
                baseMissionStream.Write(item.position);
                baseMissionStream.Write(item.rotation);
                baseMissionStream.Write(item.scale);
                baseMissionStream.Write(item.rotate);
            }

            // Geometry
            baseMissionStream.Write<U32>(mMission->geometries.size());
            for (auto &geometry: mMission->geometries)
            {
                baseMissionStream.WriteSTString(geometry.type);
                //memStream.WriteCString(geometry.name);
                baseMissionStream.Write(geometry.position);
                baseMissionStream.Write(geometry.rotation);
                baseMissionStream.Write(geometry.scale);

                // TODO: Support embedded geometry
                baseMissionStream.WriteSTString(geometry.path);
            }

            // Moving Geometry
            baseMissionStream.Write<U32>(mMission->movingGeometries.size());
            for (auto &movingGeometry: mMission->movingGeometries)
            {
                baseMissionStream.WriteSTString(movingGeometry.type);
                baseMissionStream.WriteSTString(movingGeometry.subtype);
                //memStream.WriteSTString(movingGeometry.name);
                baseMissionStream.Write(movingGeometry.position);
                baseMissionStream.Write(movingGeometry.rotation);
                baseMissionStream.Write(movingGeometry.scale);
                baseMissionStream.Write(movingGeometry.initialTargetPosition);
                baseMissionStream.Write(movingGeometry.initialPosition);
                baseMissionStream.Write(movingGeometry.looping);

                // TODO: Support embedded geometry
                baseMissionStream.WriteSTString(movingGeometry.path);
                baseMissionStream.Write(movingGeometry.indexInFile);

                baseMissionStream.Write(movingGeometry.triggered);
                if (movingGeometry.triggered)
                {
                    baseMissionStream.WriteSTString(movingGeometry.trigger.type);
                    baseMissionStream.Write(movingGeometry.trigger.position);
                    baseMissionStream.Write(movingGeometry.trigger.rotation);
                    baseMissionStream.Write(movingGeometry.trigger.scale);
                    baseMissionStream.Write(movingGeometry.trigger.polyhedron);
                    baseMissionStream.Write(movingGeometry.trigger.targetTime);
                }

                // Moving Geometry Keyframes
                baseMissionStream.Write<U32>(movingGeometry.keyframes.size());
                for (auto &keyframe: movingGeometry.keyframes)
                {
                    baseMissionStream.Write(keyframe.position);
                    baseMissionStream.Write(keyframe.rotation);
                    baseMissionStream.Write(keyframe.scale);
                    baseMissionStream.Write(keyframe.seqNum);
                    baseMissionStream.WriteSTString(keyframe.type);
                    baseMissionStream.Write(keyframe.msToNext);
                    baseMissionStream.WriteSTString(keyframe.smoothingType);
                }
            }

            // Spawn Points
            baseMissionStream.Write<U32>(mMission->spawnPoints.size());
            for (auto &spawnPoint: mMission->spawnPoints)
            {
                baseMissionStream.WriteSTString(spawnPoint.className);
                baseMissionStream.WriteSTString(spawnPoint.type);
                //memStream.WriteSTString(spawnPoint.name);
                baseMissionStream.Write(spawnPoint.position);
                baseMissionStream.Write(spawnPoint.rotation);
                baseMissionStream.Write(spawnPoint.scale);
            }

            // Help Triggers
            baseMissionStream.Write<U32>(mMission->helpTriggers.size());
            for (auto &helpTrigger: mMission->helpTriggers)
            {
                baseMissionStream.Write(helpTrigger.position);
                baseMissionStream.Write(helpTrigger.rotation);
                baseMissionStream.Write(helpTrigger.scale);
                baseMissionStream.Write(helpTrigger.polyhedron);
                baseMissionStream.WriteLocalizedString(helpTrigger.msg);
            }

            // Bounds Triggers
            baseMissionStream.Write<U32>(mMission->boundsTriggers.size());
            for (auto &boundsTrigger: mMission->boundsTriggers)
            {
                baseMissionStream.Write(boundsTrigger.position);
                baseMissionStream.Write(boundsTrigger.rotation);
                baseMissionStream.Write(boundsTrigger.scale);
                baseMissionStream.Write(boundsTrigger.polyhedron);
                baseMissionStream.Write(boundsTrigger.inBounds);
            }

            // Checkpoints
            baseMissionStream.Write<U32>(mMission->checkpoints.size());
            for (auto &checkpoint: mMission->checkpoints)
            {
                baseMissionStream.Write(checkpoint.position);
                baseMissionStream.Write(checkpoint.rotation);
                baseMissionStream.Write(checkpoint.scale);
                baseMissionStream.Write(checkpoint.sequence);

                // Checkpoint Trigger
                baseMissionStream.Write(checkpoint.trigger.position);
                baseMissionStream.Write(checkpoint.trigger.rotation);
                baseMissionStream.Write(checkpoint.trigger.scale);
                baseMissionStream.Write(checkpoint.trigger.polyhedron);
            }

            // Gem Spawns
            baseMissionStream.Write<U32>( mMission->gemSpawns.size());
            for (auto &gemSpawn: mMission->gemSpawns)
            {
                baseMissionStream.WriteSTString(gemSpawn.type);
                baseMissionStream.Write(gemSpawn.position);
                baseMissionStream.Write(gemSpawn.rotation);
                baseMissionStream.Write(gemSpawn.scale);
            }

            // Preview Camera
            baseMissionStream.Write(mMission->previewCamera.position);
            baseMissionStream.Write(mMission->previewCamera.rotation);
        }

        // Mission StringTable
        std::vector<std::string> stringTable = baseMissionStream.GetStringTable();
        wrappedMissionStream.Write<U32>(stringTable.size());
        for (auto &str: stringTable)
        {
            wrappedMissionStream.WriteCString(str);
        }

        U8 *missionBytes = baseMissionStream.GetBytes();
        size_t missionSize = baseMissionStream.GetSize();

        // Write the mission file
        wrappedMissionStream.WriteBytes((char *) missionBytes, missionSize);
    }

    U8 *wrappedMissionBytes = wrappedMissionStream.GetBytes();
    size_t wrappedMissionSize = wrappedMissionStream.GetSize();
    std::vector<U8> wrappedMissionBytesVector(wrappedMissionBytes, wrappedMissionBytes + wrappedMissionSize);

    std::vector<U8> compressedMissionBytes;
    CompressMemory(wrappedMissionBytesVector, compressedMissionBytes);

    file.Write<U32>(compressedMissionBytes.size());
    file.WriteBytes((char*)compressedMissionBytes.data(), compressedMissionBytes.size());

//    file.Write7BitEncodedInt((U32)wrappedMissionSize);
//    file.WriteBytes((char*)wrappedMissionBytes, wrappedMissionSize);

    return true;
}