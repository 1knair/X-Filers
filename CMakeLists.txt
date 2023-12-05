cmake_minimum_required(VERSION 3.24)
project(P3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_subdirectory(matplotplusplus)

add_executable(P3
        Graph.h
        main.cpp
        UFOSightings.h)

target_link_libraries(P3 PUBLIC matplot)
