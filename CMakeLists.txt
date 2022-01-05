cmake_minimum_required(VERSION 3.7)
project(SemestralkaTicTacToe C)

set(CMAKE_C_STANDARD 99)

add_executable(SemestralkaTicTacToe main.c Client.h Server.h)

target_link_libraries(SemestralkaTicTacToe pthread)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

target_link_libraries(SemestralkaTicTacToe ${SDL2_LIBRARIES})
