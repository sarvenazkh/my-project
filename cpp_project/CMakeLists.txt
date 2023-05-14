cmake_minimum_required(VERSION 3.24)
project(ClassOfLife)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ClassOfLife
        main.cpp
        cell.h cell.cpp)
