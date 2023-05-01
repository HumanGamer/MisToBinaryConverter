cmake_minimum_required(VERSION 3.25)
project(MisToBinaryConverter)

set(CMAKE_CXX_STANDARD 17)

set(MAIN_SRC
    # Sources
    main.cpp
    Mission.cpp
    MissionLoaderText.cpp
    Strings.cpp
    Util.cpp
    MissionParser/Tokenizer.cpp
    MissionParser/Parser.cpp
    MissionParser/Statement.cpp
    MissionParser/ObjectDefinition.cpp
    MissionParser/VariableMap.cpp
    LevelFile.cpp
    FileStream.cpp

    # Headers
    platform/types.h
    Mission.hpp
    MissionLoaderText.hpp
    Strings.hpp
    Util.hpp
    MissionParser/Tokenizer.hpp
    MissionParser/TokenTypes.inc
    MissionParser/Parser.hpp
    MissionParser/Statement.hpp
    MissionParser/StatementKinds.inc
    MissionParser/ObjectDefinition.hpp
    MissionParser/VariableMap.hpp
    CaseInsensitiveMap.hpp
    LevelFile.hpp
    FileStream.hpp
)

add_executable(MisToBinaryConverter ${MAIN_SRC})
target_link_libraries(MisToBinaryConverter PRIVATE crossguid)
add_dependencies(MisToBinaryConverter crossguid)
target_include_directories(MisToBinaryConverter PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
