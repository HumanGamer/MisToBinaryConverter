#include "Mission.hpp"
#include <iostream>

void Mission::debugPrint()
{
    Mission* mission = this;

    std::cout << "Mission name: " << mission->info.name << std::endl;
    std::cout << "Mission description: " << mission->info.description << std::endl;
    std::cout << "Mission startHelpText: " << mission->info.startHelpText << std::endl;
    std::cout << "Mission type: " << mission->info.type << std::endl;
    std::cout << "Mission artist: " << mission->info.artist << std::endl;
    std::cout << "Mission guid: " << mission->info.guid << std::endl;
    std::cout << "Mission level index: " << mission->info.levelIndex << std::endl;
    std::cout << "Mission include in level list: " << mission->info.includeInLevelList << std::endl;
    std::cout << "Mission game mode: " << mission->info.gameMode << std::endl;
    std::cout << "Mission game type: " << mission->info.gameType << std::endl;
    std::cout << "Mission time limit: " << mission->info.timeLimit << std::endl;
    std::cout << "Mission par goal score: " << mission->info.parGoal.score << std::endl;
    std::cout << "Mission par goal time: " << mission->info.parGoal.time << std::endl;
    std::cout << "Mission gold goal score: " << mission->info.goldGoal.score << std::endl;
    std::cout << "Mission gold goal time: " << mission->info.goldGoal.time << std::endl;
    std::cout << "Mission difficulty: " << mission->info.difficulty << std::endl;
    std::cout << "Mission num gems: " << mission->info.numGems << std::endl;
    std::cout << "Mission gem group radius: " << mission->info.gemGroupRadius << std::endl;
    std::cout << "Mission max gems per group: " << mission->info.maxGemsPerGroup << std::endl;
    std::cout << "Mission sky: " << mission->info.sky << std::endl;

    std::cout << "Mission shapes: " << std::endl;
    for (auto& shape : mission->shapes)
    {
        std::cout << "Shape " << shape.name << std::endl;
        std::cout << "(" << std::endl;
        std::cout << "\tShape type: " << shape.type << std::endl;
        std::cout << "\tShape position: " << shape.position.x << ", " << shape.position.y << ", " << shape.position.z << std::endl;
        std::cout << "\tShape rotation: " << shape.rotation.x << ", " << shape.rotation.y << ", " << shape.rotation.z << ", " << shape.rotation.angle << std::endl;
        std::cout << "\tShape scale: " << shape.scale.x << ", " << shape.scale.y << ", " << shape.scale.z << std::endl;
        std::cout << ")" << std::endl;
    }

    std::cout << "Mission Geometry: " << std::endl;
    for (auto& shape : mission->geometries)
    {
        std::cout << "Geometry " << shape.name << std::endl;
        std::cout << "(" << std::endl;
        std::cout << "\tGeometry type: " << shape.type << std::endl;
        std::cout << "\tGeometry position: " << shape.position.x << ", " << shape.position.y << ", " << shape.position.z << std::endl;
        std::cout << "\tGeometry rotation: " << shape.rotation.x << ", " << shape.rotation.y << ", " << shape.rotation.z << ", " << shape.rotation.angle << std::endl;
        std::cout << "\tGeometry scale: " << shape.scale.x << ", " << shape.scale.y << ", " << shape.scale.z << std::endl;
        std::cout << "\tGeometry file: " << shape.path << std::endl;
        std::cout << ")" << std::endl;
    }

    std::cout << "Mission Items: " << std::endl;
    for (auto& item : mission->items)
    {
        std::cout << "Item " << item.name << std::endl;
        std::cout << "(" << std::endl;
        std::cout << "\tItem type: " << item.type << std::endl;
        std::cout << "\tItem position: " << item.position.x << ", " << item.position.y << ", " << item.position.z << std::endl;
        std::cout << "\tItem rotation: " << item.rotation.x << ", " << item.rotation.y << ", " << item.rotation.z << ", " << item.rotation.angle << std::endl;
        std::cout << "\tItem scale: " << item.scale.x << ", " << item.scale.y << ", " << item.scale.z << std::endl;
        std::cout << "\trotate: " << item.rotate << std::endl;
        std::cout << ")" << std::endl;
    }

    std::cout << "Mission Spawn Points: " << std::endl;
    for (auto& spawn : mission->spawnPoints)
    {
        std::cout << "Spawn Point " << spawn.name << std::endl;
        std::cout << "(" << std::endl;
        std::cout << "\tSpawn Point type: " << spawn.type << std::endl;
        std::cout << "\tSpawn Point className: " << spawn.className << std::endl;
        std::cout << "\tSpawn Point position: " << spawn.position.x << ", " << spawn.position.y << ", " << spawn.position.z << std::endl;
        std::cout << "\tSpawn Point rotation: " << spawn.rotation.x << ", " << spawn.rotation.y << ", " << spawn.rotation.z << ", " << spawn.rotation.angle << std::endl;
        std::cout << "\tSpawn Point scale: " << spawn.scale.x << ", " << spawn.scale.y << ", " << spawn.scale.z << std::endl;
        std::cout << ")" << std::endl;
    }

    std::cout << "Help Triggers: " << std::endl;
    for (auto& trigger : mission->helpTriggers)
    {
        std::cout << "Help Trigger" << std::endl;
        std::cout << "(" << std::endl;
        std::cout << "\tHelp Trigger position: " << trigger.position.x << ", " << trigger.position.y << ", " << trigger.position.z << std::endl;
        std::cout << "\tHelp Trigger rotation: " << trigger.rotation.x << ", " << trigger.rotation.y << ", " << trigger.rotation.z << ", " << trigger.rotation.angle << std::endl;
        std::cout << "\tHelp Trigger scale: " << trigger.scale.x << ", " << trigger.scale.y << ", " << trigger.scale.z << std::endl;
        std::cout << "\tHelp Trigger Polyhedron: " << trigger.polyhedron << std::endl;
        std::cout << "\tHelp Trigger message: " << trigger.msg << std::endl;
        std::cout << ")" << std::endl;
    }

    std::cout << "Bounds Triggers: " << std::endl;
    for (auto& trigger : mission->boundsTriggers)
    {
        std::cout << "Bounds Trigger" << std::endl;
        std::cout << "(" << std::endl;
        std::cout << "\tBounds Trigger position: " << trigger.position.x << ", " << trigger.position.y << ", " << trigger.position.z << std::endl;
        std::cout << "\tBounds Trigger rotation: " << trigger.rotation.x << ", " << trigger.rotation.y << ", " << trigger.rotation.z << ", " << trigger.rotation.angle << std::endl;
        std::cout << "\tBounds Trigger scale: " << trigger.scale.x << ", " << trigger.scale.y << ", " << trigger.scale.z << std::endl;
        std::cout << "\tBounds Trigger Polyhedron: " << trigger.polyhedron << std::endl;
        std::cout << "\tBounds Trigger InBounds: " << (trigger.inBounds ? "true" : "false") << std::endl;
        std::cout << ")" << std::endl;
    }

    std::cout << "Moving Geometry: " << std::endl;
    for (auto& geometry : mission->movingGeometries)
    {
        std::cout << "Moving Geometry" << std::endl;
        std::cout << "(" << std::endl;
        std::cout << "\tMoving Geometry type: " << geometry.type << std::endl;
        std::cout << "\tMoving Geometry subtype: " << geometry.subtype << std::endl;
        std::cout << "\tMoving Geometry position: " << geometry.position.x << ", " << geometry.position.y << ", " << geometry.position.z << std::endl;
        std::cout << "\tMoving Geometry rotation: " << geometry.rotation.x << ", " << geometry.rotation.y << ", " << geometry.rotation.z << ", " << geometry.rotation.angle << std::endl;
        std::cout << "\tMoving Geometry scale: " << geometry.scale.x << ", " << geometry.scale.y << ", " << geometry.scale.z << std::endl;
        std::cout << "\tMoving Geometry file: " << geometry.path << std::endl;
        std::cout << "\tMoving Geometry indexInFile: " << geometry.indexInFile << std::endl;
        std::cout << "\tMoving Geometry initialTargetPosition: " << geometry.initialTargetPosition << std::endl;
        std::cout << "\tMoving Geometry initialPosition: " << geometry.initialPosition << std::endl;
        std::cout << "\tMoving Geometry Looping: " << (geometry.looping ? "true" : "false") << std::endl;
        std::cout << "\tMoving Geometry Triggered: " << (geometry.triggered ? "true" : "false") << std::endl;
        if (geometry.triggered)
        {
            std::cout << "\tMoving Geometry Trigger:" << std::endl;
            std::cout << "\t(" << std::endl;
            std::cout << "\t\tMoving Geometry Trigger type: " << geometry.trigger.type << std::endl;
            std::cout << "\t\tMoving Geometry Trigger position: " << geometry.trigger.position.x << ", " << geometry.trigger.position.y << ", " << geometry.trigger.position.z << std::endl;
            std::cout << "\t\tMoving Geometry Trigger rotation: " << geometry.trigger.rotation.x << ", " << geometry.trigger.rotation.y << ", " << geometry.trigger.rotation.z << ", " << geometry.trigger.rotation.angle << std::endl;
            std::cout << "\t\tMoving Geometry Trigger scale: " << geometry.trigger.scale.x << ", " << geometry.trigger.scale.y << ", " << geometry.trigger.scale.z << std::endl;
            std::cout << "\t\tMoving Geometry Trigger Polyhedron: " << geometry.trigger.polyhedron << std::endl;
            std::cout << "\t\tMoving Geometry Trigger TargetTime: " << geometry.trigger.targetTime << std::endl;
            std::cout << "\t)" << std::endl;
        }

        std::cout << "\tMoving Geometry Keyframes: " << std::endl;
        for (auto& keyframe : geometry.keyframes)
        {
            std::cout << "\tKeyframe" << std::endl;
            std::cout << "\t(" << std::endl;
            std::cout << "\t\tKeyframe position: " << keyframe.position.x << ", " << keyframe.position.y << ", " << keyframe.position.z << std::endl;
            std::cout << "\t\tKeyframe rotation: " << keyframe.rotation.x << ", " << keyframe.rotation.y << ", " << keyframe.rotation.z << ", " << keyframe.rotation.angle << std::endl;
            std::cout << "\t\tKeyframe scale: " << keyframe.scale.x << ", " << keyframe.scale.y << ", " << keyframe.scale.z << std::endl;
            std::cout << "\t\tKeyframe seqNum: " << keyframe.seqNum << std::endl;
            std::cout << "\t\tKeyframe type: " << keyframe.type << std::endl;
            std::cout << "\t\tKeyframe msToNext: " << keyframe.msToNext << std::endl;
            std::cout << "\t\tKeyframe smoothingType: " << keyframe.smoothingType << std::endl;
            std::cout << "\t)" << std::endl;
        }

        std::cout << ")" << std::endl;
    }

    std::cout << "Checkpoints: " << std::endl;
    for (auto& checkpoint : mission->checkpoints)
    {
        std::cout << "Checkpoint" << std::endl;
        std::cout << "(" << std::endl;
        std::cout << "\tCheckpoint position: " << checkpoint.position.x << ", " << checkpoint.position.y << ", " << checkpoint.position.z << std::endl;
        std::cout << "\tCheckpoint rotation: " << checkpoint.rotation.x << ", " << checkpoint.rotation.y << ", " << checkpoint.rotation.z << ", " << checkpoint.rotation.angle << std::endl;
        std::cout << "\tCheckpoint scale: " << checkpoint.scale.x << ", " << checkpoint.scale.y << ", " << checkpoint.scale.z << std::endl;
        std::cout << "\tCheckpoint sequence: " << checkpoint.sequence << std::endl;
        std::cout << "\tTrigger:" << std::endl;
        std::cout << "\t(" << std::endl;
        std::cout << "\t\tCheckpoint Trigger position: " << checkpoint.trigger.position.x << ", " << checkpoint.trigger.position.y << ", " << checkpoint.trigger.position.z << std::endl;
        std::cout << "\t\tCheckpoint Trigger rotation: " << checkpoint.trigger.rotation.x << ", " << checkpoint.trigger.rotation.y << ", " << checkpoint.trigger.rotation.z << ", " << checkpoint.trigger.rotation.angle << std::endl;
        std::cout << "\t\tCheckpoint Trigger scale: " << checkpoint.trigger.scale.x << ", " << checkpoint.trigger.scale.y << ", " << checkpoint.trigger.scale.z << std::endl;
        std::cout << "\t\tCheckpoint Trigger polyhedron: " << checkpoint.trigger.polyhedron << std::endl;
        std::cout << "\t)" << std::endl;
        std::cout << ")" << std::endl;
    }

    std::cout << "Gem Spawns: " << std::endl;
    for (auto& gemSpawn : mission->gemSpawns)
    {
        std::cout << "Gem Spawn" << std::endl;
        std::cout << "(" << std::endl;
        std::cout << "\tGem Spawn type: " << gemSpawn.type << std::endl;
        std::cout << "\tGem Spawn position: " << gemSpawn.position.x << ", " << gemSpawn.position.y << ", " << gemSpawn.position.z << std::endl;
        std::cout << "\tGem Spawn rotation: " << gemSpawn.rotation.x << ", " << gemSpawn.rotation.y << ", " << gemSpawn.rotation.z << ", " << gemSpawn.rotation.angle << std::endl;
        std::cout << "\tGem Spawn scale: " << gemSpawn.scale.x << ", " << gemSpawn.scale.y << ", " << gemSpawn.scale.z << std::endl;
        std::cout << ")" << std::endl;
    }

    std::cout << "Mission Preview Camera: " << std::endl;
    std::cout << "(" << std::endl;
    std::cout << "\tPreview Camera position: " << mission->previewCamera.position.x << ", " << mission->previewCamera.position.y << ", " << mission->previewCamera.position.z << std::endl;
    std::cout << "\tPreview Camera rotation: " << mission->previewCamera.rotation.x << ", " << mission->previewCamera.rotation.y << ", " << mission->previewCamera.rotation.z << ", " << mission->previewCamera.rotation.angle << std::endl;
    std::cout << ")" << std::endl;
}