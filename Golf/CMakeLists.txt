cmake_minimum_required(VERSION 3.10)
project(GolfGame)

set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(GolfGame
    main.cpp
    Game.cpp
    Game.h
    Ball.cpp
    Ball.h
    Hole.cpp
    Hole.h
)

target_link_libraries(GolfGame ${SDL2_LIBRARIES})