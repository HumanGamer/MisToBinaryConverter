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

    // TODO: Moving Platforms

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

    // TODO: Help Triggers

    // TODO: Bounds Triggers

    // TODO: Checkpoints

    // TODO: Multiplayer Gem Spawns

    std::cout << "Mission Preview Camera: " << std::endl;
    std::cout << "(" << std::endl;
    std::cout << "\tPreview Camera position: " << mission->previewCamera.position.x << ", " << mission->previewCamera.position.y << ", " << mission->previewCamera.position.z << std::endl;
    std::cout << "\tPreview Camera rotation: " << mission->previewCamera.rotation.x << ", " << mission->previewCamera.rotation.y << ", " << mission->previewCamera.rotation.z << ", " << mission->previewCamera.rotation.angle << std::endl;
    std::cout << ")" << std::endl;
}