#pragma once

#include <cstdint>
#include <string>

typedef uint8_t     U8;
typedef int8_t      S8;

typedef uint16_t    U16;
typedef int16_t     S16;

typedef uint32_t    U32;
typedef int32_t     S32;

typedef uint64_t    U64;
typedef int64_t     S64;

typedef float       F32;
typedef double      F64;

struct Point
{
    F32 x;
    F32 y;
    F32 z;

    Point::Point()
    {
        x = 0;
        y = 0;
        z = 0;
    }
};

struct AngAxis
{
    F32 x;
    F32 y;
    F32 z;
    F32 angle;

    AngAxis::AngAxis()
    {
        x = 1;
        y = 0;
        z = 0;
        angle = 0;
    }
};

struct Polyhedron
{
    Point origin;
    Point points[3];

    Polyhedron::Polyhedron()
    {
        origin = Point();
        points[0] = Point();
        points[1] = Point();
        points[2] = Point();
    }

    std::string str()
    {
        return std::string("Polyhedron(") +
                std::to_string(origin.x) + ", " +
                std::to_string(origin.y) + ", " +
                std::to_string(origin.z) + ", " +
                std::to_string(points[0].x) + ", " +
                std::to_string(points[0].y) + ", " +
                std::to_string(points[0].z) + ", " +
                std::to_string(points[1].x) + ", " +
                std::to_string(points[1].y) + ", " +
                std::to_string(points[1].z) + ", " +
                std::to_string(points[2].x) + ", " +
                std::to_string(points[2].y) + ", " +
                std::to_string(points[2].z) + ")";
    }
};
