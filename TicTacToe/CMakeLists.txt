cmake_minimum_required(VERSION 3.10)
project(TicTacToeGame)

set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(TicTacToeGame
    main.cpp
    Game.cpp
    Game.h
    Board.cpp
    Board.h
)

target_link_libraries(TicTacToeGame ${SDL2_LIBRARIES})