#pragma once

#include <platform/types.h>
#include <string>

struct Mission
{
    struct Info
    {
        std::string name;
        std::string description;
        bool localized;
        std::string type;
        std::string artist;
        std::string guid;
        U32 levelIndex;
        bool includeInLevelList;
        std::string gameMode;
        std::string gameType;
        U32 timeLimit;
        union Goal
        {
            U32 time;
            U32 score;
        };
        Goal parGoal;
        Goal goldGoal;
        U32 difficulty;
        U32 numGems;
        U32 gemGroupRadius;
        U32 maxGemsPerGroup;
    };
    Info info;

    struct Environment
    {
        std::string sky;
        std::string clouds;
        U32 renderDistance;
    };
    Environment environment;

    struct Shapes
    {
        std::string type;
        std::string name;
        Point position;
        AngAxis rotation;
        Point scale;
    };
    U32 numShapes;
    Shapes** shapes;

    struct Item
    {
        std::string type;
        std::string name;
        Point position;
        AngAxis rotation;
        Point scale;
        bool rotate;
    };
    U32 numItems;
    Item** items;

    struct Geometry
    {
        std::string type;
        std::string name;
        Point position;
        AngAxis rotation;
        Point scale;

        // TODO: For the new format we will change this to support being embedded in the file
        std::string path;
    };
    U32 numGeometries;
    Geometry** geometries;

    struct MovingGeometry
    {
        std::string type;
        std::string subtype;
        std::string name;
        Point position;
        AngAxis rotation;
        Point scale;
        S32 initialTargetPosition;
        bool looping;

        // TODO: For the new format we will change this to support being embedded in the file
        std::string path;
        U32 indexInFile;

        struct KeyFrame
        {
            Point position;
            AngAxis rotation;
            Point scale;
            U32 timeToNext;
            U32 smoothingType;
        };
        U32 numKeyFrames;
        KeyFrame** keyframes;
    };
    U32 numMovingGeometries;
    MovingGeometry** movingGeometries;

    struct SpawnPoint
    {
        Point position;
        AngAxis rotation;
    };
    U32 numSpawnPoints;
    SpawnPoint** spawnPoints;

    struct HelpTrigger
    {
        Point position;
        AngAxis rotation;
        Point scale;

        std::string msg;
        bool localized;
    };
    U32 numHelpTriggers;
    HelpTrigger** helpTriggers;

    struct BoundsTrigger
    {
        Point position;
        AngAxis rotation;
        Point scale;

        bool inBounds;
    };
    U32 numBoundsTriggers;
    BoundsTrigger** boundsTriggers;

    struct Checkpoint
    {
        Point position;
        AngAxis rotation;
        Point scale;
        U32 sequence;

        struct Trigger
        {
            Point position;
            AngAxis rotation;
            Point scale;
        };
        Trigger trigger;
    };
    U32 numCheckpoints;
    Checkpoint** checkpoints;

    struct PreviewCamera
    {
        Point position;
        AngAxis rotation;
    };
    PreviewCamera previewCamera;
};