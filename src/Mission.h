#pragma once

#include <platform/types.h>

struct Mission
{
    struct Info
    {
        const char* name;
        const char* description;
        bool localized;
        const char* artist;
        const char* guid;
        U32 levelIndex;
        bool includeInLevelList;
        const char* gameMode;
        const char* gameType;
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
        const char* sky;
        const char* clouds;
        U32 renderDistance;
        bool hasAstrolabe;
    };
    Environment environment;

    struct Item
    {
        const char* type;
        const char* name;
        Point position;
        AngAxis rotation;
        Point scale;
        bool rotate;
    };
    U32 numItems;
    Item** items;

    struct Geometry
    {
        const char* type;
        const char* name;
        Point position;
        AngAxis rotation;
        Point scale;

        // TODO: For the new format we will change this to support being embedded in the file
        const char* path;
    };
    U32 numGeometries;
    Geometry** geometries;

    struct MovingGeometry
    {
        const char* type;
        const char* subtype;
        const char* name;
        Point position;
        AngAxis rotation;
        Point scale;
        S32 initialTargetPosition;
        bool looping;

        // TODO: For the new format we will change this to support being embedded in the file
        const char* path;
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

        const char* msg;
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