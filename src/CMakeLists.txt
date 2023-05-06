cmake_minimum_required(VERSION 3.25)
project(MisToBinaryConverter)

set(CMAKE_CXX_STANDARD 17)

set(MAIN_SRC
    # Sources
    main.cpp
    core/strings.cpp
    core/util.cpp
    core/streams/stream.cpp
    core/streams/fileStream.cpp
    core/streams/memStream.cpp
    core/compression.cpp
    mission/mission.cpp
    mission/parser/tokenizer.cpp
    mission/parser/parser.cpp
    mission/parser/statement.cpp
    mission/parser/objectDefinition.cpp
    mission/parser/variableMap.cpp
    mission/parser/textLoader.cpp
    interior/interiorResource.cpp
    levelFile.cpp

    # Headers
    platform/types.h
    core/strings.hpp
    core/util.hpp
    core/streams/stream.hpp
    core/streams/fileStream.hpp
    core/streams/memStream.hpp
    core/caseInsensitiveMap.hpp
    core/compression.hpp
    mission/mission.hpp
    mission/parser/tokenizer.hpp
    mission/parser/tokenTypes.inc
    mission/parser/parser.hpp
    mission/parser/statement.hpp
    mission/parser/statementKinds.inc
    mission/parser/objectDefinition.hpp
    mission/parser/variableMap.hpp
    mission/parser/textLoader.hpp
    interior/interiorResource.hpp
    levelFile.hpp
)

add_executable(MisToBinaryConverter ${MAIN_SRC})
target_link_libraries(MisToBinaryConverter PRIVATE crossguid zlibstatic)
add_dependencies(MisToBinaryConverter crossguid zlibstatic)
target_include_directories(MisToBinaryConverter PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
