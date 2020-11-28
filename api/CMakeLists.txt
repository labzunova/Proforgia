cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 14)

set(HEADER_FILES
        include/entities/File.h
        include/entities/Room.h
        include/entities/Session.h
        include/entities/User.h
        include/external_api/View.h
        include/Handler.h
        include/page/PageManager.h
        include/activity/ActivityManager.h
        include/activity/ActivityCustomer.h
        include/activity/ActivityUser.h
        include/page/PageCustomer.h
        include/page/PageUser.h
        include/Worker.h
        )

set(SOURCE_FILES
        main.cpp
        src/Handler.cpp
        src/PageCustomer.cpp
        src/PageUser.cpp
        src/ActivityCustomer.cpp
        src/ActivityUser.cpp
        src/ActivityManager.cpp
        src/Worker.cpp
        )

include_directories(include include/activity include/page)
add_executable(server ${HEADER_FILES} ${SOURCE_FILES})
