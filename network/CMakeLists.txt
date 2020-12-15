set(SERVER_LIB server_lib)

set(UNIT_TESTS
        tests/tests.cpp
        tests/network/parser_tests.cpp)

set(INCLUDE
        include
        src
        )

set(HEADER_FILES_SERVER
        include/Connection.h
        include/Connection_queue.h
        include/Parser.h
        include/Request_handler.h
        include/Server.h
        )

set(SOURCE_FILES_SERVER
        src/Connection.cpp
        src/Connection_queue.cpp
        src/Parser.cpp
        src/Request_handler.cpp
        src/Server.cpp
        )

SET(Boost_USE_STATIC_LIBS ON)
FIND_PACKAGE(Boost REQUIRED COMPONENTS log)
find_package(GTest)
include_directories(${Boost_INCLUDE_DIRS})

add_library(${SERVER_LIB} STATIC ${SOURCE_FILES_SERVER} ${HEADER_FILES_SERVER})
target_include_directories(${SERVER_LIB} PUBLIC ${INCLUDE} ${UNIT_TESTS})

#add_executable(tests_core ${SOURCE_FILES_TESTS})
#target_link_libraries(tests_core gtest gmock gtest_main rt -ldl pthread ${CORE_LIB})