cmake_minimum_required(VERSION 3.12)
project(robots)

set(CMAKE_CXX_STANDARD 14)

add_executable(robots main.cpp Robot.cpp Robot.h Position.cpp Position.h Map.cpp Map.h)