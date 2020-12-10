cmake_minimum_required(VERSION 3.15)
project(Proforgia)

# SET(MYCOMPILE_FLAGS " -lpthread -o ")
# add_definitions(${MYCOMPILE_FLAGS})
# add_compile_options(-pthread)

set(CMAKE_CXX_STANDARD 17)

#------------------tempates engine---------------------
set(wt_views
        wt_templates/NLTemplate.cpp
        wt_templates/BaseTemplate.cpp
        wt_templates/Login/LoginTemplate.cpp
        wt_templates/SignUp/SignUpTemplate.cpp
        wt_templates/Profile/ProfileTemplate.cpp
        wt_templates/TemplateWrapper.cpp)
include_directories(wt_templates)

add_library(TemplatesEngine ${wt_views})

add_subdirectory(database)
add_subdirectory(core)

SET(Boost_USE_STATIC_LIBS ON)
FIND_PACKAGE(Boost REQUIRED COMPONENTS log)
include_directories(${Boost_INCLUDE_DIRS})

# add_executable(Proforgia main.cpp)
# target_link_libraries(Proforgia database_lib)

include_directories("${PROJECT_SOURCE_DIR}/network")
include_directories("${PROJECT_SOURCE_DIR}/core")

set(UNIT_TESTS
        tests/tests.cpp
        tests/network/parser_tests.cpp)

add_executable(Proforgia main.cpp network/connection/Connection.cpp network/connection/Connection.h network/server/Server.cpp network/server/Server.h network/parser/Parser.cpp network/parser/Parser.h network/connection_queue/Connection_queue.cpp network/connection_queue/Connection_queue.h network/request/Request.cpp network/request/Request.h)
target_link_libraries(Proforgia core_lib)
target_link_libraries(Proforgia boost_system pthread ${Boost_LIBRARIES})



#---------------------------google-tests---------------------------

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif ()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif ()

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
endif ()

# Now simply link against gtest or gtest_main as needed. Eg
#target_link_libraries(example gtest_main)
#add_test(NAME example_test COMMAND example)

add_executable(Tests ${UNIT_TESTS})

#add "rt" flag  if not on mac
target_link_libraries(Tests gtest gtest_main -ldl pthread)

#-----------------------------end-google-tests-----------------------------

