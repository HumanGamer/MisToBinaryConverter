cmake_minimum_required(VERSION 3.25)
project(crossguid)

set(CMAKE_CXX_STANDARD 17)

set(CROSSGUID_SRC
    # sources
    src/guid.cpp

    # headers
    include/crossguid/guid.hpp
)

add_library(crossguid STATIC ${CROSSGUID_SRC})
target_include_directories(crossguid PUBLIC include)
