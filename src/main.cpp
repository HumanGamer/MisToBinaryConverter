#include <iostream>

#include "mis_parser.h"

int main(int argc, const char** argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    const char* fileName = argv[1];

    std::cout << "Parsing file: " << fileName << std::endl;

    Mission mis_file;
    if (!parse_mis_file(fileName, &mis_file))
    {
        std::cout << "Failed to parse file" << std::endl;
        return 1;
    }

    std::cout << "Mission name: " << mis_file.info.name << std::endl;
    std::cout << "Mission description: " << mis_file.info.description << std::endl;
    std::cout << "Mission name localized: " << mis_file.info.nameLocalized << std::endl;
    std::cout << "Mission type: " << mis_file.info.type << std::endl;
    std::cout << "Mission artist: " << mis_file.info.artist << std::endl;
    std::cout << "Mission guid: " << mis_file.info.guid << std::endl;
    std::cout << "Mission level index: " << mis_file.info.levelIndex << std::endl;
    std::cout << "Mission include in level list: " << mis_file.info.includeInLevelList << std::endl;
    std::cout << "Mission game mode: " << mis_file.info.gameMode << std::endl;
    std::cout << "Mission game type: " << mis_file.info.gameType << std::endl;
    std::cout << "Mission time limit: " << mis_file.info.timeLimit << std::endl;
    std::cout << "Mission par goal score: " << mis_file.info.parGoal.score << std::endl;
    std::cout << "Mission par goal time: " << mis_file.info.parGoal.time << std::endl;
    std::cout << "Mission gold goal score: " << mis_file.info.goldGoal.score << std::endl;
    std::cout << "Mission gold goal time: " << mis_file.info.goldGoal.time << std::endl;
    std::cout << "Mission difficulty: " << mis_file.info.difficulty << std::endl;
    std::cout << "Mission num gems: " << mis_file.info.numGems << std::endl;
    std::cout << "Mission gem group radius: " << mis_file.info.gemGroupRadius << std::endl;
    std::cout << "Mission max gems per group: " << mis_file.info.maxGemsPerGroup << std::endl;
    std::cout << "Mission sky: " << mis_file.info.sky << std::endl;

    std::cout << "Mission shapes: " << std::endl;
    for (auto& shape : mis_file.shapes)
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
    for (auto& shape : mis_file.geometries)
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
    for (auto& item : mis_file.items)
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
    for (auto& spawn : mis_file.spawnPoints)
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
    std::cout << "\tPreview Camera position: " << mis_file.previewCamera.position.x << ", " << mis_file.previewCamera.position.y << ", " << mis_file.previewCamera.position.z << std::endl;
    std::cout << "\tPreview Camera rotation: " << mis_file.previewCamera.rotation.x << ", " << mis_file.previewCamera.rotation.y << ", " << mis_file.previewCamera.rotation.z << ", " << mis_file.previewCamera.rotation.angle << std::endl;
    std::cout << ")" << std::endl;

    std::cout << "Done!" << std::endl;

    return 0;
}
