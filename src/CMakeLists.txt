cmake_minimum_required(VERSION 3.25)
project(MisToBinaryConverter)

set(CMAKE_CXX_STANDARD 17)

set(MAIN_SRC
    # Sources
    main.cpp
    Mission.cpp
    MissionLoaderText.cpp
    Strings.cpp
    MissionParser/Tokenizer.cpp
    MissionParser/Parser.cpp
    MissionParser/Statement.cpp
    MissionParser/ObjectDefinition.cpp

    # Headers
    platform/types.h
    Mission.hpp
    MissionLoaderText.hpp
    Strings.hpp
    MissionParser/Tokenizer.hpp
    MissionParser/TokenTypes.inc
    MissionParser/Parser.hpp
    MissionParser/Statement.hpp
    MissionParser/StatementKinds.inc
    MissionParser/ObjectDefinition.hpp
)

add_executable(MisToBinaryConverter ${MAIN_SRC})
target_include_directories(MisToBinaryConverter PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
