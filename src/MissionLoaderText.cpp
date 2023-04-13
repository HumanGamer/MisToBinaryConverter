#include "MissionLoaderText.hpp"
#include "Util.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <MissionParser/Tokenizer.hpp>
#include <MissionParser/Parser.hpp>
#include <MissionParser/VariableMap.hpp>

#define GET_VAR_MAP(object) \
    MissionParser::VariableMap variables; \
    if (!object.getVariableMap(&variables)) \
        return false

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
    GET_VAR_MAP(object);

    mission->info.name = variables.getString("name");
    mission->info.description = variables.getString("desc");
    mission->info.type = variables.getString("type");
    mission->info.artist = variables.getString("artist");
    if (mission->info.artist.empty())
        mission->info.artist = "Unknown";
    mission->info.startHelpText = variables.getString("startHelpText");
    mission->info.guid = variables.getString("guid");
    mission->info.levelIndex = variables.getInt("level");
    mission->info.includeInLevelList = variables.getBool("include");
    std::string gameMode = variables.getString("gameMode");
    if (gameMode.empty())
        gameMode = "race";
    if (equalsIgnoreCase(gameMode, "scrum"))
        gameMode = "hunt";
    mission->info.gameMode = gameMode;
    mission->info.multiplayer = equalsIgnoreCase(variables.getString("gameType"), "multiplayer");
    if (equalsIgnoreCase(gameMode, "hunt"))
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
                GET_VAR_MAP(child);
                mission->info.sky = variables.getString("materialList");
                if (!mission->info.sky.empty())
                {
                    // strip to just file name
                    size_t pos = mission->info.sky.find_last_of('/');
                    if (pos != std::string::npos)
                        mission->info.sky = mission->info.sky.substr(pos + 1);

                    // strip extension
                    pos = mission->info.sky.find_last_of('.');
                    if (pos != std::string::npos)
                        mission->info.sky = mission->info.sky.substr(0, pos);

                    // strip sky_ prefix
                    if (mission->info.sky.find("sky_") == 0)
                        mission->info.sky = mission->info.sky.substr(4);
                }
                continue;
            }

            if (equalsIgnoreCase(child.mClassName, "StaticShape"))
            {
                GET_VAR_MAP(child);
                Mission::Shape shape;
                shape.type = variables.getString("dataBlock");
                //shape.name = child.mName;
                shape.position = variables.getPoint("position");
                shape.rotation = variables.getAngAxis("rotation");
                shape.scale = variables.getPoint("scale");
                mission->shapes.push_back(shape);
                continue;
            }

            if (equalsIgnoreCase(child.mClassName, "InteriorInstance"))
            {
                GET_VAR_MAP(child);
                Mission::Geometry geometry;
                geometry.type = "Interior";
                //geometry.name = child.mName;
                geometry.position = variables.getPoint("position");
                geometry.rotation = variables.getAngAxis("rotation");
                geometry.scale = variables.getPoint("scale");
                geometry.path = variables.getString("interiorFile");
                mission->geometries.push_back(geometry);

                continue;
            }

            if (equalsIgnoreCase(child.mClassName, "Item"))
            {
                GET_VAR_MAP(child);
                Mission::Item item;
                //item.name = child.mName;
                item.position = variables.getPoint("position");
                item.rotation = variables.getAngAxis("rotation");
                item.scale = variables.getPoint("scale");
                item.type = variables.getString("dataBlock");
                item.rotate = variables.getBool("rotate");
                mission->items.push_back(item);

                continue;
            }

            if (equalsIgnoreCase(child.mClassName, "SimGroup") && equalsIgnoreCase(child.mName, "SpawnPoints"))
            {
                for (auto& spawnPoint : child.mChildren)
                {
                    GET_VAR_MAP(spawnPoint);
                    Mission::SpawnPoint point;
                    //point.name = spawnPoint.mName;
                    point.position = variables.getPoint("position");
                    point.rotation = variables.getAngAxis("rotation");
                    point.scale = variables.getPoint("scale");
                    point.type = variables.getString("dataBlock");
                    point.className = spawnPoint.mClassName;
                    mission->spawnPoints.push_back(point);
                }
                continue;
            }

            if (equalsIgnoreCase(child.mClassName, "SimGroup") && equalsIgnoreCase(child.mName, "GemSpawns"))
            {
                for (auto& gemSpawn : child.mChildren)
                {
                    if (!equalsIgnoreCase(gemSpawn.mClassName, "SpawnSphere"))
                        continue;
                    GET_VAR_MAP(gemSpawn);
                    if (!equalsIgnoreCase(variables.getString("dataBlock"), "GemSpawnSphereMarker"))
                        continue;
                    Mission::GemSpawn spawn;
                    spawn.position = variables.getPoint("position");
                    spawn.rotation = variables.getAngAxis("rotation");
                    spawn.scale = variables.getPoint("scale");
                    spawn.type = variables.getString("gemDataBlock");
                    if (spawn.type.empty())
                        spawn.type = "GemItem";
                    mission->gemSpawns.push_back(spawn);
                }
                continue;
            }

            if (equalsIgnoreCase(child.mClassName, "SimGroup"))
            {
                Mission::MovingGeometry movingGeometry;
                movingGeometry.triggered = false;
                bool isMovingGeometry = false;
                for (auto& obj : child.mChildren)
                {
                    if (equalsIgnoreCase(obj.mClassName, "PathedInterior"))
                    {
                        GET_VAR_MAP(obj);
                        isMovingGeometry = true;

                        //movingGeometry.name = obj.mName;
                        movingGeometry.type = "Interior";
                        movingGeometry.subtype = variables.getString("dataBlock");
                        movingGeometry.position = variables.getPoint("position");
                        movingGeometry.rotation = variables.getAngAxis("rotation");
                        movingGeometry.scale = variables.getPoint("scale");
                        movingGeometry.initialTargetPosition = variables.getInt("initialTargetPosition");
                        movingGeometry.initialPosition = variables.getInt("initialPosition");
                        movingGeometry.path = variables.getString("interiorResource");
                        movingGeometry.indexInFile = variables.getInt("interiorIndex");

                        break;
                    }
                }

                if (isMovingGeometry)
                {
                    for (auto& obj : child.mChildren)
                    {
                        if (equalsIgnoreCase(obj.mClassName, "Path"))
                        {
                            GET_VAR_MAP(obj);
                            movingGeometry.looping = variables.getBool("isLooping");

                            for (auto& pathNode : obj.mChildren)
                            {
                                if (!equalsIgnoreCase(pathNode.mClassName, "Marker"))
                                {
                                    std::cerr << "Non-marker in path: " << pathNode.mClassName << std::endl;
                                    continue;
                                }
                                GET_VAR_MAP(pathNode);
                                Mission::MovingGeometry::KeyFrame node;
                                node.position = variables.getPoint("position");
                                node.rotation = variables.getAngAxis("rotation");
                                node.scale = variables.getPoint("scale");
                                node.seqNum = variables.getInt("seqNum");
                                node.type = variables.getString("type");
                                node.msToNext = variables.getInt("msToNext");
                                node.smoothingType = variables.getString("smoothingType");

                                movingGeometry.keyframes.push_back(node);
                            }
                            continue;
                        }

                        if (equalsIgnoreCase(obj.mClassName, "Trigger"))
                        {
                            GET_VAR_MAP(obj);
                            movingGeometry.triggered = true;
                            Mission::MovingGeometry::Trigger trigger;
                            trigger.position = variables.getPoint("position");
                            trigger.rotation = variables.getAngAxis("rotation");
                            trigger.scale = variables.getPoint("scale");
                            trigger.type = variables.getString("dataBlock");
                            trigger.polyhedron = variables.getString("polyhedron");
                            trigger.targetTime = variables.getInt("targetTime");
                            movingGeometry.trigger = trigger;
                            continue;
                        }
                    }

                    mission->movingGeometries.push_back(movingGeometry);
                    continue;
                }


                Mission::Checkpoint checkpoint;
                bool isCheckpoint = false;
                for (auto& obj : child.mChildren)
                {
                    if (equalsIgnoreCase(obj.mClassName, "StaticShape"))
                    {
                        GET_VAR_MAP(obj);
                        if (equalsIgnoreCase(variables.getString("dataBlock"), "checkPointShape"))
                        {
                            isCheckpoint = true;

                            checkpoint.position = variables.getPoint("position");
                            checkpoint.rotation = variables.getAngAxis("rotation");
                            checkpoint.scale = variables.getPoint("scale");

                            break;
                        }
                    }
                }

                if (isCheckpoint)
                {
                    for (auto& obj : child.mChildren)
                    {
                        if (equalsIgnoreCase(obj.mClassName, "Trigger"))
                        {
                            GET_VAR_MAP(obj);
                            if (equalsIgnoreCase(variables.getString("dataBlock"), "CheckPointTrigger"))
                            {
                                Mission::Checkpoint::Trigger trigger;
                                trigger.position = variables.getPoint("position");
                                trigger.rotation = variables.getAngAxis("rotation");
                                trigger.scale = variables.getPoint("scale");
                                trigger.polyhedron = variables.getString("polyhedron");
                                checkpoint.trigger = trigger;
                                checkpoint.sequence = variables.getInt("sequence");
                                mission->checkpoints.push_back(checkpoint);
                                break;
                            }
                        }
                    }
                }

                continue;
            }

            if (equalsIgnoreCase(child.mClassName, "Trigger"))
            {
                GET_VAR_MAP(child);

                if (equalsIgnoreCase(variables.getString("dataBlock"), "HelpTrigger"))
                {
                    Mission::HelpTrigger trigger;
                    trigger.position = variables.getPoint("position");
                    trigger.rotation = variables.getAngAxis("rotation");
                    trigger.scale = variables.getPoint("scale");
                    trigger.polyhedron = variables.getString("polyhedron");
                    trigger.msg = variables.getString("text");
                    mission->helpTriggers.push_back(trigger);
                    continue;
                }

                if (equalsIgnoreCase(variables.getString("dataBlock"), "InBoundsTrigger"))
                {
                    Mission::BoundsTrigger trigger;
                    trigger.position = variables.getPoint("position");
                    trigger.rotation = variables.getAngAxis("rotation");
                    trigger.scale = variables.getPoint("scale");
                    trigger.polyhedron = variables.getString("polyhedron");
                    trigger.inBounds = true;
                    mission->boundsTriggers.push_back(trigger);
                    continue;
                }

                if (equalsIgnoreCase(variables.getString("dataBlock"), "OutOfBoundsTrigger"))
                {
                    Mission::BoundsTrigger trigger;
                    trigger.position = variables.getPoint("position");
                    trigger.rotation = variables.getAngAxis("rotation");
                    trigger.scale = variables.getPoint("scale");
                    trigger.polyhedron = variables.getString("polyhedron");
                    trigger.inBounds = false;
                    mission->boundsTriggers.push_back(trigger);
                    continue;
                }

                continue;
            }

            if (equalsIgnoreCase(child.mClassName, "SpawnSphere"))
            {
                GET_VAR_MAP(child);
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