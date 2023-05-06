#include <iostream>

#include <mission/mission.hpp>
#include <mission/parser/textLoader.hpp>
#include <core/util.hpp>
#include <interior/interiorResource.hpp>
#include <levelFile.hpp>

int main(int argc, const char** argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    const char* fileName = argv[1];

    std::cout << "Parsing file: " << fileName << std::endl;

    Mission mission;
    if (!MissionParser::LoadMissionText(fileName, &mission))
    {
        std::cout << "Failed to parse file" << std::endl;
        return 1;
    }

    //mission.debugPrint();

    std::vector<std::string> interiorPaths;

    for (auto & geometry : mission.geometries)
    {
        if (containsIgnoreCase(interiorPaths, geometry.path))
            continue;

        interiorPaths.push_back(geometry.path);
    }

    for (auto & geometry : mission.movingGeometries)
    {
        if (containsIgnoreCase(interiorPaths, geometry.path))
            continue;

        interiorPaths.push_back(geometry.path);
    }

    for (auto & interiorPath : interiorPaths)
        interiorPath = cleanPath(interiorPath);

//    for (auto& paths : interiorPaths)
//    {
//        std::cout << paths << std::endl;
//    }

    std::vector<InteriorResource*> interiors;
    for (auto& interior : interiorPaths)
    {
        // Make interior path relative to the mission file
        std::string relativeInteriorPath = getRelativePath(interior, getDirectory(getFullPath(fileName)));

        InteriorResource* interiorResource = new InteriorResource();
        if (!interiorResource->Load(relativeInteriorPath))
        {
            std::cout << "Failed to load interior: " << interior << std::endl;
            delete interiorResource;
            return 1;
        }

        interiors.push_back(interiorResource);
    }

    LevelFile levelFile;
    levelFile.SetMission(&mission);
    levelFile.SetInteriors(interiors);
    if (!levelFile.Save("test.mblv"))
    {
        std::cout << "Failed to save file" << std::endl;
        for (auto& interior : interiors)
            delete interior;
        return 1;
    }

    std::cout << "Done!" << std::endl;

    for (auto& interior : interiors)
        delete interior;

    return 0;
}
