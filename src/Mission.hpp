#pragma once

#include <platform/types.h>
#include "Strings.hpp"
#include <string>
#include <vector>

struct Mission
{
    struct Info
    {
        LocalizedString name;
        LocalizedString description;
        LocalizedString startHelpText;
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
        std::string sky;
    };
    Info info;

    struct Shape
    {
        std::string type;
        std::string name;
        Point position;
        AngAxis rotation;
        Point scale;
    };
    std::vector<Shape> shapes;

    struct Item
    {
        std::string type;
        std::string name;
        Point position;
        AngAxis rotation;
        Point scale;
        bool rotate;
    };
    std::vector<Item> items;

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
    std::vector<Geometry> geometries;

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
        std::vector<KeyFrame> keyframes;
    };
    std::vector<MovingGeometry> movingGeometries;

    struct SpawnPoint
    {
        std::string className;
        std::string type;
        std::string name;
        Point position;
        AngAxis rotation;
        Point scale;
    };
    std::vector<SpawnPoint> spawnPoints;

    struct HelpTrigger
    {
        Point position;
        AngAxis rotation;
        Point scale;
        std::string polyhedron;

        LocalizedString msg;
    };
    std::vector<HelpTrigger> helpTriggers;

    struct BoundsTrigger
    {
        Point position;
        AngAxis rotation;
        Point scale;
        std::string polyhedron;

        bool inBounds;
    };
    std::vector<BoundsTrigger*> boundsTriggers;

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
            std::string polyhedron;
        };
        Trigger trigger;
    };
    std::vector<Checkpoint> checkpoints;

    struct PreviewCamera
    {
        Point position;
        AngAxis rotation;
    };
    PreviewCamera previewCamera;
};
