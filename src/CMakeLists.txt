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
    core/streams/MemStream.cpp
    core/Compression.cpp
    mission/parser/Tokenizer.cpp
    mission/parser/Parser.cpp
    mission/parser/Statement.cpp
    mission/parser/ObjectDefinition.cpp
    mission/parser/VariableMap.cpp
    mission/parser/MissionLoaderText.cpp
    mission/Mission.cpp
    LevelFile.cpp

    # Headers
    platform/types.h
    core/Strings.hpp
    core/Util.hpp
    core/streams/Stream.hpp
    core/streams/FileStream.hpp
    core/streams/MemStream.hpp
    core/CaseInsensitiveMap.hpp
    core/Compression.hpp
    mission/parser/Tokenizer.hpp
    mission/parser/TokenTypes.inc
    mission/parser/Parser.hpp
    mission/parser/Statement.hpp
    mission/parser/StatementKinds.inc
    mission/parser/ObjectDefinition.hpp
    mission/parser/VariableMap.hpp
    mission/parser/MissionLoaderText.hpp
    mission/Mission.hpp
    LevelFile.hpp
)

add_executable(MisToBinaryConverter ${MAIN_SRC})
target_link_libraries(MisToBinaryConverter PRIVATE crossguid zlibstatic)
add_dependencies(MisToBinaryConverter crossguid zlibstatic)
target_include_directories(MisToBinaryConverter PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
