cmake_minimum_required(VERSION 3.23)
project(Projekt1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Projekt1 main.cpp character.cpp character.h field.h position.h generate.h stats.h)
