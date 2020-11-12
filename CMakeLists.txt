cmake_minimum_required(VERSION 3.17)
project(Proforgia)

set(CMAKE_CXX_STANDARD 14)

include_directories(include, interface)

add_executable(Proforgia main.cpp)

add_subdirectory(api)
