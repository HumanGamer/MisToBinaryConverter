#include <iostream>

#include "Mission.hpp"
#include <MissionParser/MissionLoaderText.hpp>
#include "LevelFile.hpp"

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
    if (!LoadMissionText(fileName, &mission))
    {
        std::cout << "Failed to parse file" << std::endl;
        return 1;
    }

    //mission.debugPrint();

    LevelFile levelFile;
    levelFile.SetMission(&mission);
    if (!levelFile.Save("test.mblv"))
    {
        std::cout << "Failed to save file" << std::endl;
        return 1;
    }

    std::cout << "Done!" << std::endl;

    return 0;
}
