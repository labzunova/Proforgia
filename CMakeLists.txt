cmake_minimum_required(VERSION 3.17)
project(Proforgia)

set(CMAKE_CXX_STANDARD 14)

add_executable(Proforgia main.cpp network/client/Connection.cpp network/client/Connection.h network/server/Server.cpp network/server/Server.h network/parser/Parser.cpp network/parser/Parser.h)