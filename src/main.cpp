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
    std::cout << "Mission localized: " << mis_file.info.localized << std::endl;
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

    std::cout << "Done!" << std::endl;

    return 0;
}
