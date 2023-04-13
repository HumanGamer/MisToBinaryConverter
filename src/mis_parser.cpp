#include "mis_parser.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <MissionParser/Tokenizer.hpp>
#include <MissionParser/Parser.hpp>

bool parse_mission(const char* filename, std::vector<MissionParser::ObjectDefinition>* const objects)
{
    std::ifstream file;
    file.open(filename, std::ios::binary);
    if (!file.is_open())
        return false;

    file.seekg(0, std::ios::end);
    std::streamsize length = file.tellg();
    file.seekg(0, std::ios::beg);

    char* file_contents = new char[length + 1];
    file.read(file_contents, length);
    file_contents[length] = '\0';
    file.close();

    MissionParser::Tokenizer tokenizer;
    auto tokens = tokenizer.parse(file_contents);

//    for (auto& token : tokens)
//    {
//        token.debugPrint();
//    }

    delete[] file_contents;

    MissionParser::Parser parser;
    parser.parse(tokens);

    //parser.debugPrint();

    *objects = parser.getObjects();

    return true;
}

bool getVariables(const MissionParser::ObjectDefinition& object, std::map<std::string, std::string>* variables)
{
    for (auto& statement : object.mStatements)
    {
        std::string name = statement.mName;
        if (statement.mParameters.size() != 1)
        {
            std::string s = "Internal error, the variable has more than one value";
            std::cerr << s << std::endl;
            //throw std::runtime_error(s);
            return false;
        }
        std::string value = statement.mParameters[0].mName;
        (*variables)[name] = value;
    }
    return true;
}

std::string getVariableValue(std::map<std::string, std::string> variables, const char* name)
{
    auto it = variables.find(name);
    if (it == variables.end())
        return "";
    return it->second;
}

bool getBoolVariableValue(std::map<std::string, std::string> variables, const char* name)
{
    auto it = variables.find(name);
    if (it == variables.end())
        return "";
    if (it->second == "true" || it->second == "1")
        return true;
    return false;
}

U32 getIntVariableValue(std::map<std::string, std::string> variables, const char* name)
{
    auto it = variables.find(name);
    if (it == variables.end())
        return 0;
    return std::stoi(it->second);
}

bool processMissionInfo(const MissionParser::ObjectDefinition& object, Mission* mission)
{
    std::map<std::string, std::string> variables;
    if (!getVariables(object, &variables))
        return false;

    std::string name = getVariableValue(variables, "name");
    mission->info.localized = name.length() > 0 && name[0] == '$';
    mission->info.name = name;
    mission->info.description = getVariableValue(variables, "desc");
    mission->info.type = getVariableValue(variables, "type");
    mission->info.artist = getVariableValue(variables, "artist");
    mission->info.guid = getVariableValue(variables, "guid");
    mission->info.levelIndex = getIntVariableValue(variables, "level");
    mission->info.includeInLevelList = getBoolVariableValue(variables, "include");
    std::string gameMode = getVariableValue(variables, "gameMode");
    if (gameMode == "")
        gameMode = "Race";
    mission->info.gameMode = gameMode;
    mission->info.gameType = getVariableValue(variables, "gameType");
    std::transform(gameMode.begin(), gameMode.end(), gameMode.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    if (gameMode == "scrum")
    {
        mission->info.timeLimit = getIntVariableValue(variables, "time");
        mission->info.parGoal.score = getIntVariableValue(variables, "score");
        mission->info.goldGoal.score = getIntVariableValue(variables, "goldScore");
    } else {
        mission->info.timeLimit = 0;
        mission->info.parGoal.time = getIntVariableValue(variables, "time");
        mission->info.goldGoal.time = getIntVariableValue(variables, "goldTime");
    }

    mission->info.difficulty = getIntVariableValue(variables, "difficulty");
    mission->info.numGems = getIntVariableValue(variables, "numGems");
    mission->info.gemGroupRadius = getIntVariableValue(variables, "gemGroupRadius");
    mission->info.maxGemsPerGroup = getIntVariableValue(variables, "maxGemsPerGroup");

    return true;
}

bool populateMissionStructure(const std::vector<MissionParser::ObjectDefinition> &objects, Mission* mission)
{
    bool success = false;
    for (auto& object : objects)
    {
        if (object.mClassName != "SimGroup" || object.mName != "MissionGroup")
            continue;

        for (auto& children : object.mChildren)
        {
            if (children.mClassName == "ScriptObject" && children.mName == "MissionInfo")
            {
                if (!processMissionInfo(children, mission))
                    return false;

                success = true;
                continue;
            }

            // TODO: Process other objects
        }
    }

    return success;
}

bool parse_mis_file(const char* filename, Mission* mission)
{
    std::vector<MissionParser::ObjectDefinition> objects;

    if (!parse_mission(filename, &objects))
        return false;

    if (!populateMissionStructure(objects, mission))
        return false;

    return true;
}