cmake_minimum_required(VERSION 3.25)
project(MisToBinaryConverter)

set(CMAKE_CXX_STANDARD 17)

set(MAIN_SRC
    # Sources
    main.cpp
    core/Strings.cpp
    core/Util.cpp
    core/streams/Stream.cpp
    core/streams/FileStream.cpp
    MissionParser/Tokenizer.cpp
    MissionParser/Parser.cpp
    MissionParser/Statement.cpp
    MissionParser/ObjectDefinition.cpp
    MissionParser/VariableMap.cpp
    Mission.cpp
    MissionLoaderText.cpp
    LevelFile.cpp

    # Headers
    platform/types.h
    core/Strings.hpp
    core/Util.hpp
    core/streams/Stream.hpp
    core/streams/FileStream.hpp
    core/CaseInsensitiveMap.hpp
    MissionParser/Tokenizer.hpp
    MissionParser/TokenTypes.inc
    MissionParser/Parser.hpp
    MissionParser/Statement.hpp
    MissionParser/StatementKinds.inc
    MissionParser/ObjectDefinition.hpp
    MissionParser/VariableMap.hpp
    Mission.hpp
    MissionLoaderText.hpp
    LevelFile.hpp
)

add_executable(MisToBinaryConverter ${MAIN_SRC})
target_link_libraries(MisToBinaryConverter PRIVATE crossguid)
add_dependencies(MisToBinaryConverter crossguid)
target_include_directories(MisToBinaryConverter PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
