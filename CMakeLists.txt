cmake_minimum_required(VERSION 3.29)
project(semestralka)

set(CMAKE_CXX_STANDARD 20)

add_executable(semestralka minesweeper.cpp
        minesweeper.hpp
        Cell.cpp
        Cell.hpp
        Board.cpp
        Board.hpp
)
