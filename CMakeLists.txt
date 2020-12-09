cmake_minimum_required(VERSION 3.15)
project(Proforgia)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(database)

add_executable(Proforgia main.cpp)

target_link_libraries(Proforgia database_lib)