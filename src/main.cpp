#include <iostream>

#include <mission/mission.hpp>
#include <mission/parser/textLoader.hpp>
#include "levelFile.hpp"

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
