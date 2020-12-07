cmake_minimum_required(VERSION 3.15)
project(Proforgia)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

# TODO: replace Users/Ivan with project root variable
include_directories(${PROJECT_SOURCE_DIR}/database/aws-sdk/install/include)
find_package(AWSSDK REQUIRED COMPONENTS s3)

find_package(PostgreSQL REQUIRED)

SET(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS log)
include_directories(${Boost_INCLUDE_DIRS})





add_executable(Proforgia main.cpp
        database/include/DataManager.h

        database/include/Utils/DBEntities.h
        database/include/Utils/ErrorCodes.h
        database/include/Utils/Rights.h

        database/include/Wrappers/DBWrapperRealisations/PostgreDBWrapper.h
        database/include/Wrappers/StorageWrapperRealisations/AmazonS3StorageWrapper.h

        database/include/Wrappers/DBWrapper.h
        database/include/Wrappers/StorageWrapper.h

        database/src/AmazonS3StorageWrapper.cpp
        database/src/PostgreDBWrapper.cpp
        database/src/DataManager.cpp
        database/src/DBEntities.cpp)
target_include_directories(Proforgia PRIVATE ${PostgreSQL_INCLUDE_DIRS})

target_link_libraries(Proforgia ${AWSSDK_LINK_LIBRARIES} ${PostgreSQL_LIBRARIES} ${Boost_LIBRARIES})