cmake_minimum_required(VERSION 3.17)
project(Proforgia)

set(MYCOMPILE_FLAGS " -lpthread -o ")
add_definitions(${MYCOMPILE_FLAGS})

set(CMAKE_CXX_STANDARD 14)

#set(Boost_USE_STATIC_LIBS ON)
#find_package(Boost REQUIRED COMPONENTS log)
#include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(network)


set(UNIT_TESTS
        tests/tests.cpp
        )

add_executable(Proforgia main.cpp)

target_link_libraries(Proforgia boost_system pthread ${Boost_LIBRARIES})
target_link_libraries(Proforgia server_lib)
#---------------------------google-tests---------------------------

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif()

# Now simply link against gtest or gtest_main as needed. Eg
#target_link_libraries(example gtest_main)
#add_test(NAME example_test COMMAND example)

add_executable(Tests ${UNIT_TESTS})
target_link_libraries(Tests gtest gtest_main -ldl pthread)

#-----------------------------end-google-tests-----------------------------
