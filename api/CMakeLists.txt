cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 14)

set(HEADER_FILES
        include/entities/File.h
        include/entities/Location.h
        include/entities/Room.h
        include/entities/Session.h
        include/entities/User.h
        include/external_api/View.h
        include/external_api/Context.h
        include/UserApi.h
        include/CustomerApi.h
        )

set(SOURCE_FILES
        main.cpp
        src/UserApi.cpp
        src/CustomerAPI.cpp
        )

include_directories(interface include)
add_executable(server ${HEADER_FILES} ${SOURCE_FILES})
