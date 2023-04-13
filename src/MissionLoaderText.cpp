#include "MissionLoaderText.hpp"
#include "Util.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <MissionParser/Tokenizer.hpp>
#include <MissionParser/Parser.hpp>
#include <MissionParser/VariableMap.hpp>

#define GET_VAR_MAP(object, onFail) \
    MissionParser::VariableMap variables; \
    if (!object.getVariableMap(&variables)) \
        onFail

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

bool processMissionInfo(const MissionParser::ObjectDefinition& object, Mission* mission)
{
    GET_VAR_MAP(object, return false);

    mission->info.name = variables.getString("name");
    mission->info.description = variables.getString("desc");
    mission->info.type = variables.getString("type");
    mission->info.artist = variables.getString("artist");
    mission->info.startHelpText = variables.getString("startHelpText");
    mission->info.guid = variables.getString("guid");
    mission->info.levelIndex = variables.getInt("level");
    mission->info.includeInLevelList = variables.getBool("include");
    std::string gameMode = variables.getString("gameMode");
    if (gameMode.empty())
        gameMode = "race";
    mission->info.gameMode = gameMode;
    mission->info.gameType = variables.getString("gameType");
    if (equalsIgnoreCase(gameMode, "scrum"))
    {
        mission->info.timeLimit = variables.getInt("time");
        mission->info.parGoal.score = variables.getInt("score");
        mission->info.goldGoal.score = variables.getInt("goldScore");
    } else {
        mission->info.timeLimit = 0;
        mission->info.parGoal.time = variables.getInt("time");
        mission->info.goldGoal.time = variables.getInt("goldTime");
    }

    mission->info.difficulty = variables.getInt("difficulty");
    mission->info.numGems = variables.getInt("numGems");
    mission->info.gemGroupRadius = variables.getInt("gemGroupRadius");
    mission->info.maxGemsPerGroup = variables.getInt("maxGemsPerGroup");

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
                GET_VAR_MAP(child, return false);
                mission->info.sky = variables.getString("materialList");
                if (!mission->info.sky.empty())
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
                GET_VAR_MAP(child, return false);
                Mission::Shape shape;
                shape.type = variables.getString("dataBlock");
                shape.name = child.mName;
                shape.position = variables.getPoint("position");
                shape.rotation = variables.getAngAxis("rotation");
                shape.scale = variables.getPoint("scale");
                mission->shapes.push_back(shape);
                continue;
            }

            if (equalsIgnoreCase(child.mClassName, "InteriorInstance"))
            {
                GET_VAR_MAP(child, return false);
                Mission::Geometry geometry;
                geometry.type = "Interior";
                geometry.name = child.mName;
                geometry.position = variables.getPoint("position");
                geometry.rotation = variables.getAngAxis("rotation");
                geometry.scale = variables.getPoint("scale");
                geometry.path = variables.getString("interiorFile");
                mission->geometries.push_back(geometry);

                continue;
            }

            if (equalsIgnoreCase(child.mClassName, "Item"))
            {
                GET_VAR_MAP(child, return false);
                Mission::Item item;
                item.name = child.mName;
                item.position = variables.getPoint("position");
                item.rotation = variables.getAngAxis("rotation");
                item.scale = variables.getPoint("scale");
                item.type = variables.getString("dataBlock");
                item.rotate = variables.getBool("rotate");
                mission->items.push_back(item);

                continue;
            }

            // TODO: Moving Platforms

            if (equalsIgnoreCase(child.mClassName, "SimGroup") && equalsIgnoreCase(child.mName, "SpawnPoints"))
            {
                for (auto& spawnPoint : child.mChildren)
                {
                    GET_VAR_MAP(spawnPoint, return false);
                    Mission::SpawnPoint point;
                    point.name = spawnPoint.mName;
                    point.position = variables.getPoint("position");
                    point.rotation = variables.getAngAxis("rotation");
                    point.scale = variables.getPoint("scale");
                    point.type = variables.getString("dataBlock");
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
                GET_VAR_MAP(child, return false);
                if (variables.getString("dataBlock") != "CameraSpawnSphereMarker")
                {
                    std::cerr << "Unknown SpawnSphere object found" << std::endl;
                    continue;
                }

                mission->previewCamera.position = variables.getPoint("position");
                mission->previewCamera.rotation = variables.getAngAxis("rotation");
                continue;
            }
        }
    }

    return success;
}

bool LoadMissionText(const char* filename, Mission* mission)
{
    std::vector<MissionParser::ObjectDefinition> objects;

    if (!parse_mission(filename, &objects))
        return false;

    if (!populateMissionStructure(objects, mission))
        return false;

    return true;
}