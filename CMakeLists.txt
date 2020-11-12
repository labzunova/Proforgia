cmake_minimum_required(VERSION 3.17)
project(Proforgia)

set(CMAKE_CXX_STANDARD 14)

include_directories("${PROJECT_SOURCE_DIR}/templates/include")
add_subdirectory(templates/src)

add_executable(Proforgia main.cpp templates/include/Context.h templates/src/Context.cpp templates/src/View.cpp templates/include/View.h templates/include/Loader.h templates/include/Parser.h templates/src/Parser.cpp templates/include/Part.h templates/src/Part.cpp templates/include/QueueOfPart.h templates/src/QueueOfPart.cpp templates/src/Loader.cpp)