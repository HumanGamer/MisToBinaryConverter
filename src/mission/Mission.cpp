#include "Mission.hpp"
#include <core/Compression.hpp>
#include <core/streams/MemStream.hpp>
#include <core/Util.hpp>
#include <iostream>
#include <algorithm>

// -----------------------------------------------------------------------------

bool Mission::write(Stream& stream, bool zlibCompression, bool valueCompression)
{
    std::vector<U8> mission;
    if (zlibCompression)
        this->getCompressedBytes(mission, valueCompression);
    else
        this->getBytes(mission, valueCompression);

    stream.Write<U32>(mission.size());
    stream.WriteBytes((char*)mission.data(), mission.size());

    return true;
}

// -----------------------------------------------------------------------------

bool Mission::getCompressedBytes(std::vector<U8> &outData, bool valueCompression)
{
    std::vector<U8> missionBytes;
    this->getBytes(missionBytes, valueCompression);

    CompressMemory(missionBytes, outData);

    return true;
}

// -----------------------------------------------------------------------------

bool Mission::getBytes(std::vector<U8> &outData, bool valueCompression)
{
    MemStream wrappedMissionStream;
    {
        if (valueCompression)
            wrappedMissionStream.EnableCompression();
        else
            wrappedMissionStream.DisableCompression();

        MemStream baseMissionStream;
        {
            if (valueCompression)
                baseMissionStream.EnableCompression();
            else
                baseMissionStream.DisableCompression();

            // mission info
            baseMissionStream.WriteLocalizedString(this->info.name);
            baseMissionStream.WriteLocalizedString(this->info.description);
            baseMissionStream.WriteLocalizedString(this->info.startHelpText);

            baseMissionStream.Write(this->info.guid);

            baseMissionStream.WriteSTString(this->info.type);
            baseMissionStream.WriteSTString(this->info.artist);
            baseMissionStream.WriteSTString(this->info.gameMode);
            baseMissionStream.WriteSTString(this->info.sky);

            baseMissionStream.Write(this->info.levelIndex);
            baseMissionStream.Write(this->info.includeInLevelList);
            baseMissionStream.Write(this->info.difficulty);

            baseMissionStream.Write(this->info.multiplayer);
            if (this->info.multiplayer)
            {
                baseMissionStream.Write(this->info.timeLimit);
                baseMissionStream.Write(this->info.parGoal.score);
                baseMissionStream.Write(this->info.goldGoal.score);
                baseMissionStream.Write(this->info.numGems);
                baseMissionStream.Write(this->info.gemGroupRadius);
                baseMissionStream.Write(this->info.maxGemsPerGroup);
            } else
            {
                baseMissionStream.Write(this->info.parGoal.time);
                baseMissionStream.Write(this->info.goldGoal.time);
            }

            // Shapes
            baseMissionStream.Write<U32>(this->shapes.size());
            for (auto &shape: this->shapes)
            {
                baseMissionStream.WriteSTString(shape.type);
                //memStream.WriteSTString(shape.name);
                baseMissionStream.Write(shape.position);
                baseMissionStream.Write(shape.rotation);
                baseMissionStream.Write(shape.scale);
            }

            // Items
            baseMissionStream.Write<U32>(this->items.size());
            for (auto &item: this->items)
            {
                baseMissionStream.WriteSTString(item.type);
                //memStream.WriteCString(item.name);
                baseMissionStream.Write(item.position);
                baseMissionStream.Write(item.rotation);
                baseMissionStream.Write(item.scale);
                baseMissionStream.Write(item.rotate);
            }

            // Geometry
            baseMissionStream.Write<U32>(this->geometries.size());
            for (auto &geometry: this->geometries)
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
            baseMissionStream.Write<U32>(this->movingGeometries.size());
            for (auto &movingGeometry: this->movingGeometries)
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
            baseMissionStream.Write<U32>(this->spawnPoints.size());
            for (auto &spawnPoint: this->spawnPoints)
            {
                baseMissionStream.WriteSTString(spawnPoint.className);
                baseMissionStream.WriteSTString(spawnPoint.type);
                //memStream.WriteSTString(spawnPoint.name);
                baseMissionStream.Write(spawnPoint.position);
                baseMissionStream.Write(spawnPoint.rotation);
                baseMissionStream.Write(spawnPoint.scale);
            }

            // Help Triggers
            baseMissionStream.Write<U32>(this->helpTriggers.size());
            for (auto &helpTrigger: this->helpTriggers)
            {
                baseMissionStream.Write(helpTrigger.position);
                baseMissionStream.Write(helpTrigger.rotation);
                baseMissionStream.Write(helpTrigger.scale);
                baseMissionStream.Write(helpTrigger.polyhedron);
                baseMissionStream.WriteLocalizedString(helpTrigger.msg);
            }

            // Bounds Triggers
            baseMissionStream.Write<U32>(this->boundsTriggers.size());
            for (auto &boundsTrigger: this->boundsTriggers)
            {
                baseMissionStream.Write(boundsTrigger.position);
                baseMissionStream.Write(boundsTrigger.rotation);
                baseMissionStream.Write(boundsTrigger.scale);
                baseMissionStream.Write(boundsTrigger.polyhedron);
                baseMissionStream.Write(boundsTrigger.inBounds);
            }

            // Checkpoints
            baseMissionStream.Write<U32>(this->checkpoints.size());
            for (auto &checkpoint: this->checkpoints)
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
            baseMissionStream.Write<U32>( this->gemSpawns.size());
            for (auto &gemSpawn: this->gemSpawns)
            {
                baseMissionStream.WriteSTString(gemSpawn.type);
                baseMissionStream.Write(gemSpawn.position);
                baseMissionStream.Write(gemSpawn.rotation);
                baseMissionStream.Write(gemSpawn.scale);
            }

            // Preview Camera
            baseMissionStream.Write(this->previewCamera.position);
            baseMissionStream.Write(this->previewCamera.rotation);
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

    U8* buffer = wrappedMissionStream.GetBytes();
    size_t size = wrappedMissionStream.GetSize();

    outData = std::vector<U8>(buffer, buffer + size);

    return true;
}

// -----------------------------------------------------------------------------

void Mission::debugPrint()
{
    Mission* mission = this;

    if (!mission->info.name.Empty())
        std::cout << "name: " << mission->info.name << std::endl;
    if (!mission->info.description.Empty())
        std::cout << "description: " << mission->info.description << std::endl;
    if (!mission->info.startHelpText.Empty())
        std::cout << "startHelpText: " << mission->info.startHelpText << std::endl;
    std::cout << "type: " << mission->info.type << std::endl;
    if (!mission->info.artist.empty())
        std::cout << "artist: " << mission->info.artist << std::endl;
    std::cout << "guid: " << guidToString(mission->info.guid) << std::endl;
    std::cout << "levelIndex: " << mission->info.levelIndex << std::endl;
    std::cout << "includeInLevelList: " << mission->info.includeInLevelList << std::endl;
    std::cout << "gameMode: " << mission->info.gameMode << std::endl;
    std::cout << "multiplayer: " << (mission->info.multiplayer ? "true" : "false") << std::endl;
    if (mission->info.gameMode == "race")
    {
        std::cout << "parGoal.time: " << formatTime(mission->info.parGoal.time) << std::endl;
        std::cout << "goldGoal.time: " << formatTime(mission->info.goldGoal.time) << std::endl;
    }
    else
    {
        std::cout << "timeLimit: " << formatTime(mission->info.timeLimit) << std::endl;
        std::cout << "parGoal.score: " << mission->info.parGoal.score << std::endl;
        std::cout << "goldGoal.score: " << mission->info.goldGoal.score << std::endl;
    }
    std::cout << "difficulty: " << mission->info.difficulty << std::endl;
    if (mission->info.gameMode == "hunt")
    {
        std::cout << "numGems: " << mission->info.numGems << std::endl;
        std::cout << "gemGroupRadius: " << mission->info.gemGroupRadius << std::endl;
        std::cout << "maxGemsPerGroup: " << mission->info.maxGemsPerGroup << std::endl;
    }
    std::cout << "sky: " << mission->info.sky << std::endl;

    //std::cout << "Shapes: " << std::endl;
    for (auto& shape : mission->shapes)
    {
        //std::cout << "Shape " << shape.name << std::endl;
        std::cout << "Shape" << std::endl;
        std::cout << "(" << std::endl;
        std::cout << "\ttype: " << shape.type << std::endl;
        std::cout << "\tposition: " << shape.position.x << ", " << shape.position.y << ", " << shape.position.z << std::endl;
        std::cout << "\trotation: " << shape.rotation.x << ", " << shape.rotation.y << ", " << shape.rotation.z << ", " << shape.rotation.angle << std::endl;
        std::cout << "\tscale: " << shape.scale.x << ", " << shape.scale.y << ", " << shape.scale.z << std::endl;
        std::cout << ")" << std::endl;
    }

    //std::cout << "Geometry: " << std::endl;
    for (auto& shape : mission->geometries)
    {
        //std::cout << "Geometry " << shape.name << std::endl;
        std::cout << "Geometry" << std::endl;
        std::cout << "(" << std::endl;
        std::cout << "\ttype: " << shape.type << std::endl;
        std::cout << "\tposition: " << shape.position.x << ", " << shape.position.y << ", " << shape.position.z << std::endl;
        std::cout << "\trotation: " << shape.rotation.x << ", " << shape.rotation.y << ", " << shape.rotation.z << ", " << shape.rotation.angle << std::endl;
        std::cout << "\tscale: " << shape.scale.x << ", " << shape.scale.y << ", " << shape.scale.z << std::endl;
        std::cout << "\tpath: " << shape.path << std::endl;
        std::cout << ")" << std::endl;
    }

    //std::cout << "Items: " << std::endl;
    for (auto& item : mission->items)
    {
        //std::cout << "Item " << item.name << std::endl;
        std::cout << "Item" << std::endl;
        std::cout << "(" << std::endl;
        std::cout << "\ttype: " << item.type << std::endl;
        std::cout << "\tposition: " << item.position.x << ", " << item.position.y << ", " << item.position.z << std::endl;
        std::cout << "\trotation: " << item.rotation.x << ", " << item.rotation.y << ", " << item.rotation.z << ", " << item.rotation.angle << std::endl;
        std::cout << "\tscale: " << item.scale.x << ", " << item.scale.y << ", " << item.scale.z << std::endl;
        std::cout << "\trotate: " << item.rotate << std::endl;
        std::cout << ")" << std::endl;
    }

    //std::cout << "SpawnPoints: " << std::endl;
    for (auto& spawn : mission->spawnPoints)
    {
        //std::cout << "SpawnPoint " << spawn.name << std::endl;
        std::cout << "SpawnPoint" << std::endl;
        std::cout << "(" << std::endl;
        std::cout << "\ttype: " << spawn.type << std::endl;
        std::cout << "\tclassName: " << spawn.className << std::endl;
        std::cout << "\tposition: " << spawn.position.x << ", " << spawn.position.y << ", " << spawn.position.z << std::endl;
        std::cout << "\trotation: " << spawn.rotation.x << ", " << spawn.rotation.y << ", " << spawn.rotation.z << ", " << spawn.rotation.angle << std::endl;
        std::cout << "\tscale: " << spawn.scale.x << ", " << spawn.scale.y << ", " << spawn.scale.z << std::endl;
        std::cout << ")" << std::endl;
    }

    //std::cout << "HelpTriggers: " << std::endl;
    for (auto& trigger : mission->helpTriggers)
    {
        std::cout << "HelpTrigger" << std::endl;
        std::cout << "(" << std::endl;
        std::cout << "\tposition: " << trigger.position.x << ", " << trigger.position.y << ", " << trigger.position.z << std::endl;
        std::cout << "\trotation: " << trigger.rotation.x << ", " << trigger.rotation.y << ", " << trigger.rotation.z << ", " << trigger.rotation.angle << std::endl;
        std::cout << "\tscale: " << trigger.scale.x << ", " << trigger.scale.y << ", " << trigger.scale.z << std::endl;
        std::cout << "\tpolyhedron: " << trigger.polyhedron.str() << std::endl;
        std::cout << "\tmessage: " << trigger.msg << std::endl;
        std::cout << ")" << std::endl;
    }

    //std::cout << "BoundsTriggers: " << std::endl;
    for (auto& trigger : mission->boundsTriggers)
    {
        std::cout << "BoundsTrigger" << std::endl;
        std::cout << "(" << std::endl;
        std::cout << "\tposition: " << trigger.position.x << ", " << trigger.position.y << ", " << trigger.position.z << std::endl;
        std::cout << "\trotation: " << trigger.rotation.x << ", " << trigger.rotation.y << ", " << trigger.rotation.z << ", " << trigger.rotation.angle << std::endl;
        std::cout << "\tscale: " << trigger.scale.x << ", " << trigger.scale.y << ", " << trigger.scale.z << std::endl;
        std::cout << "\tpolyhedron: " << trigger.polyhedron.str() << std::endl;
        std::cout << "\tinBounds: " << (trigger.inBounds ? "true" : "false") << std::endl;
        std::cout << ")" << std::endl;
    }

    //std::cout << "MovingGeometry: " << std::endl;
    for (auto& geometry : mission->movingGeometries)
    {
        std::cout << "MovingGeometry" << std::endl;
        std::cout << "(" << std::endl;
        std::cout << "\ttype: " << geometry.type << std::endl;
        std::cout << "\tsubtype: " << geometry.subtype << std::endl;
        std::cout << "\tposition: " << geometry.position.x << ", " << geometry.position.y << ", " << geometry.position.z << std::endl;
        std::cout << "\trotation: " << geometry.rotation.x << ", " << geometry.rotation.y << ", " << geometry.rotation.z << ", " << geometry.rotation.angle << std::endl;
        std::cout << "\tscale: " << geometry.scale.x << ", " << geometry.scale.y << ", " << geometry.scale.z << std::endl;
        std::cout << "\tfile: " << geometry.path << std::endl;
        std::cout << "\tindexInFile: " << geometry.indexInFile << std::endl;
        std::cout << "\tinitialTargetPosition: " << geometry.initialTargetPosition << std::endl;
        std::cout << "\tinitialPosition: " << geometry.initialPosition << std::endl;
        std::cout << "\tlooping: " << (geometry.looping ? "true" : "false") << std::endl;
        std::cout << "\ttriggered: " << (geometry.triggered ? "true" : "false") << std::endl;
        if (geometry.triggered)
        {
            std::cout << "\tTrigger:" << std::endl;
            std::cout << "\t(" << std::endl;
            std::cout << "\t\ttype: " << geometry.trigger.type << std::endl;
            std::cout << "\t\tposition: " << geometry.trigger.position.x << ", " << geometry.trigger.position.y << ", " << geometry.trigger.position.z << std::endl;
            std::cout << "\t\trotation: " << geometry.trigger.rotation.x << ", " << geometry.trigger.rotation.y << ", " << geometry.trigger.rotation.z << ", " << geometry.trigger.rotation.angle << std::endl;
            std::cout << "\t\tscale: " << geometry.trigger.scale.x << ", " << geometry.trigger.scale.y << ", " << geometry.trigger.scale.z << std::endl;
            std::cout << "\t\tpolyhedron: " << geometry.trigger.polyhedron.str() << std::endl;
            std::cout << "\t\ttargetTime: " << geometry.trigger.targetTime << std::endl;
            std::cout << "\t)" << std::endl;
        }

        std::cout << "\tKeyframes: " << std::endl;
        for (auto& keyframe : geometry.keyframes)
        {
            std::cout << "\tKeyframe" << std::endl;
            std::cout << "\t(" << std::endl;
            std::cout << "\t\tposition: " << keyframe.position.x << ", " << keyframe.position.y << ", " << keyframe.position.z << std::endl;
            std::cout << "\t\trotation: " << keyframe.rotation.x << ", " << keyframe.rotation.y << ", " << keyframe.rotation.z << ", " << keyframe.rotation.angle << std::endl;
            std::cout << "\t\tscale: " << keyframe.scale.x << ", " << keyframe.scale.y << ", " << keyframe.scale.z << std::endl;
            std::cout << "\t\tseqNum: " << keyframe.seqNum << std::endl;
            std::cout << "\t\ttype: " << keyframe.type << std::endl;
            std::cout << "\t\tmsToNext: " << keyframe.msToNext << std::endl;
            std::cout << "\t\tsmoothingType: " << keyframe.smoothingType << std::endl;
            std::cout << "\t)" << std::endl;
        }

        std::cout << ")" << std::endl;
    }

    //std::cout << "Checkpoints: " << std::endl;
    for (auto& checkpoint : mission->checkpoints)
    {
        std::cout << "Checkpoint" << std::endl;
        std::cout << "(" << std::endl;
        std::cout << "\tposition: " << checkpoint.position.x << ", " << checkpoint.position.y << ", " << checkpoint.position.z << std::endl;
        std::cout << "\trotation: " << checkpoint.rotation.x << ", " << checkpoint.rotation.y << ", " << checkpoint.rotation.z << ", " << checkpoint.rotation.angle << std::endl;
        std::cout << "\tscale: " << checkpoint.scale.x << ", " << checkpoint.scale.y << ", " << checkpoint.scale.z << std::endl;
        std::cout << "\tsequence: " << checkpoint.sequence << std::endl;
        std::cout << "\tTrigger:" << std::endl;
        std::cout << "\t(" << std::endl;
        std::cout << "\t\tposition: " << checkpoint.trigger.position.x << ", " << checkpoint.trigger.position.y << ", " << checkpoint.trigger.position.z << std::endl;
        std::cout << "\t\trotation: " << checkpoint.trigger.rotation.x << ", " << checkpoint.trigger.rotation.y << ", " << checkpoint.trigger.rotation.z << ", " << checkpoint.trigger.rotation.angle << std::endl;
        std::cout << "\t\tscale: " << checkpoint.trigger.scale.x << ", " << checkpoint.trigger.scale.y << ", " << checkpoint.trigger.scale.z << std::endl;
        std::cout << "\t\tpolyhedron: " << checkpoint.trigger.polyhedron.str() << std::endl;
        std::cout << "\t)" << std::endl;
        std::cout << ")" << std::endl;
    }

    //std::cout << "GemSpawns: " << std::endl;
    for (auto& gemSpawn : mission->gemSpawns)
    {
        std::cout << "GemSpawn" << std::endl;
        std::cout << "(" << std::endl;
        std::cout << "\ttype: " << gemSpawn.type << std::endl;
        std::cout << "\tposition: " << gemSpawn.position.x << ", " << gemSpawn.position.y << ", " << gemSpawn.position.z << std::endl;
        std::cout << "\trotation: " << gemSpawn.rotation.x << ", " << gemSpawn.rotation.y << ", " << gemSpawn.rotation.z << ", " << gemSpawn.rotation.angle << std::endl;
        std::cout << "\tscale: " << gemSpawn.scale.x << ", " << gemSpawn.scale.y << ", " << gemSpawn.scale.z << std::endl;
        std::cout << ")" << std::endl;
    }

    std::cout << "PreviewCamera" << std::endl;
    std::cout << "(" << std::endl;
    std::cout << "\tposition: " << mission->previewCamera.position.x << ", " << mission->previewCamera.position.y << ", " << mission->previewCamera.position.z << std::endl;
    std::cout << "\trotation: " << mission->previewCamera.rotation.x << ", " << mission->previewCamera.rotation.y << ", " << mission->previewCamera.rotation.z << ", " << mission->previewCamera.rotation.angle << std::endl;
    std::cout << ")" << std::endl;
}