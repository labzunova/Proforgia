cmake_minimum_required(VERSION 3.17)
project(Proforgia)

SET(MYCOMPILE_FLAGS " -lpthread -o ")
add_definitions(${MYCOMPILE_FLAGS})
#add_compile_options(-pthread)

set(CMAKE_CXX_STANDARD 14)

add_executable(Proforgia main.cpp network/client/Connection.cpp network/client/Connection.h network/server/Server.cpp network/server/Server.h network/parser/Parser.cpp network/parser/Parser.h network/connection_loop/Connection_loop.cpp network/connection_loop/Connection_loop.h network/request/Request.cpp network/request/Request.h network/reply/Reply.cpp network/reply/Reply.h)
target_link_libraries(Proforgia boost_system pthread)

include_directories("${PROJECT_SOURCE_DIR}/network/client")
include_directories("${PROJECT_SOURCE_DIR}/network/connection_loop")
include_directories("${PROJECT_SOURCE_DIR}/network/server")
include_directories("${PROJECT_SOURCE_DIR}/network/request")
include_directories("${PROJECT_SOURCE_DIR}/network/reply")
include_directories("${PROJECT_SOURCE_DIR}/network/parser")
