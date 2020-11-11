cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 14)

set(HEADER_FILES
        include/Server.h
        include/GeneratorKey.h
        include/BdManager.h
        include/steps.h
        include/alg_assembly.h
        include/Context.h
        include/DataProcessing.h
        )

set(SOURCE_FILES
        main.cpp
        src/GeneratorKey.cpp
        src/Server.cpp
        src/steps.cpp
        src/alg_assembly.cpp
        src/steps_bd.cpp
        )

include_directories(interface include)
add_executable(server ${HEADER_FILES} ${SOURCE_FILES})
