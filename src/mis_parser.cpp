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

Point getPointVariableValue(std::map<std::string, std::string> variables, const char* name)
{
    auto it = variables.find(name);
    if (it == variables.end())
        return Point();

    Point p;
    sscanf_s(it->second.c_str(), "%f %f %f", &p.x, &p.y, &p.z);

    return p;
}

AngAxis getAngAxisVariableValue(std::map<std::string, std::string> variables, const char* name)
{
    auto it = variables.find(name);
    if (it == variables.end())
        return AngAxis();

    AngAxis a;
    sscanf_s(it->second.c_str(), "%f %f %f %f", &a.x, &a.y, &a.z, &a.angle);

    return a;
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

bool equalsIgnoreCase(const std::string s1, const std::string s2)
{
    if (s1.length() != s2.length())
        return false;

    std::string s1_lower = s1;
    std::string s2_lower = s2;
    std::transform(s1_lower.begin(), s1_lower.end(), s1_lower.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    std::transform(s2_lower.begin(), s2_lower.end(), s2_lower.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    return s1_lower == s2_lower;
}

bool processMissionInfo(const MissionParser::ObjectDefinition& object, Mission* mission)
{
    std::map<std::string, std::string> variables;
    if (!getVariables(object, &variables))
        return false;

    std::string name = getVariableValue(variables, "name");
    mission->info.nameLocalized = name.length() > 0 && name[0] == '$';
    if (mission->info.nameLocalized && name.rfind("$Text::", 0) == 0)
        name = name.substr(7);
    mission->info.name = name;
    mission->info.description = getVariableValue(variables, "desc");
    mission->info.type = getVariableValue(variables, "type");
    mission->info.artist = getVariableValue(variables, "artist");
    mission->info.guid = getVariableValue(variables, "guid");
    mission->info.levelIndex = getIntVariableValue(variables, "level");
    mission->info.includeInLevelList = getBoolVariableValue(variables, "include");
    std::string gameMode = getVariableValue(variables, "gameMode");
    if (gameMode == "")
        gameMode = "race";
    mission->info.gameMode = gameMode;
    mission->info.gameType = getVariableValue(variables, "gameType");
    if (equalsIgnoreCase(gameMode, "scrum"))
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

        for (auto& child : object.mChildren)
        {
            if (equalsIgnoreCase(child.mClassName, "ScriptObject") && equalsIgnoreCase(child.mName, "MissionInfo"))
            {
                if (!processMissionInfo(child, mission))
                    return false;

                success = true;
                continue;
            }

            if (equalsIgnoreCase(child.mClassName, "Sky"))
            {
                std::map<std::string, std::string> variables;
                if (!getVariables(child, &variables))
                    return false;
                mission->info.sky = getVariableValue(variables, "materialList");
                if (mission->info.sky != "")
                {
                    // strip to just file name
                    size_t pos = mission->info.sky.find_last_of('/');
                    if (pos != std::string::npos)
                        mission->info.sky = mission->info.sky.substr(pos + 1);
                }
                continue;
            }

            if (equalsIgnoreCase(child.mClassName, "StaticShape"))
            {
                std::map<std::string, std::string> variables;
                if (!getVariables(child, &variables))
                    return false;
                Mission::Shape shape;
                shape.type = getVariableValue(variables, "dataBlock");
                shape.name = child.mName;
                shape.position = getPointVariableValue(variables, "position");
                shape.rotation = getAngAxisVariableValue(variables, "rotation");
                shape.scale = getPointVariableValue(variables, "scale");
                mission->shapes.push_back(shape);
                continue;
            }

            if (equalsIgnoreCase(child.mClassName, "InteriorInstance"))
            {
                std::map<std::string, std::string> variables;
                if (!getVariables(child, &variables))
                    return false;

                Mission::Geometry geometry;
                geometry.type = "Interior";
                geometry.name = child.mName;
                geometry.position = getPointVariableValue(variables, "position");
                geometry.rotation = getAngAxisVariableValue(variables, "rotation");
                geometry.scale = getPointVariableValue(variables, "scale");
                geometry.path = getVariableValue(variables, "interiorFile");
                mission->geometries.push_back(geometry);

                continue;
            }

            if (equalsIgnoreCase(child.mClassName, "Item"))
            {
                std::map<std::string, std::string> variables;
                if (!getVariables(child, &variables))
                    return false;

                Mission::Item item;
                item.name = child.mName;
                item.position = getPointVariableValue(variables, "position");
                item.rotation = getAngAxisVariableValue(variables, "rotation");
                item.scale = getPointVariableValue(variables, "scale");
                item.type = getVariableValue(variables, "dataBlock");
                item.rotate = getBoolVariableValue(variables, "rotate");
                mission->items.push_back(item);

                continue;
            }

            // TODO: Moving Platforms

            if (equalsIgnoreCase(child.mClassName, "SimGroup") && equalsIgnoreCase(child.mName, "SpawnPoints"))
            {
                for (auto& spawnPoint : child.mChildren)
                {
                    std::map<std::string, std::string> variables;
                    if (!getVariables(spawnPoint, &variables))
                        return false;

                    Mission::SpawnPoint point;
                    point.name = spawnPoint.mName;
                    point.position = getPointVariableValue(variables, "position");
                    point.rotation = getAngAxisVariableValue(variables, "rotation");
                    point.scale = getPointVariableValue(variables, "scale");
                    point.type = getVariableValue(variables, "dataBlock");
                    point.className = spawnPoint.mClassName;
                    mission->spawnPoints.push_back(point);
                }
                continue;
            }

            // TODO: Help Triggers

            // TODO: Bounds Triggers

            // TODO: Checkpoints

            // TODO: Multiplayer Gem Spawns

            if (equalsIgnoreCase(child.mClassName, "SpawnSphere"))
            {
                std::map<std::string, std::string> variables;
                if (!getVariables(child, &variables))
                    return false;

                if (getVariableValue(variables, "dataBlock") != "CameraSpawnSphereMarker")
                {
                    std::cerr << "Unknown SpawnSphere object found" << std::endl;
                    continue;
                }

                mission->previewCamera.position = getPointVariableValue(variables, "position");
                mission->previewCamera.rotation = getAngAxisVariableValue(variables, "rotation");
                continue;
            }
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