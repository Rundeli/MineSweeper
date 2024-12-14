project(MineSweeper)

cmake_minimum_required(VERSION 3.22)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(MineSweeper minesweeper.C)