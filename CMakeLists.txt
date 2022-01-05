cmake_minimum_required(VERSION 3.7)
project(SemestralkaTicTacToe C)

set(CMAKE_C_STANDARD 99)

add_executable(SemestralkaTicTacToe main.c)

target_link_libraries(SemestralkaTicTacToe pthread)

