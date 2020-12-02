cmake_minimum_required(VERSION 3.15)
project(Proforgia)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

include_directories(/Users/Ivan/Proforgia/database/aws-sdk/install/include)

find_package(AWSSDK REQUIRED COMPONENTS s3)

add_executable(Proforgia main.cpp
        database/include/DataManager.h

        database/include/Utils/DBEntities.h
        database/include/Utils/ErrorCodes.h
        database/include/Utils/Rights.h

        database/include/Wrappers/DBWrapperRealisations/PostgreDBWrapper.h
        database/include/Wrappers/StorageWrapperRealisations/AmazonS3StorageWrapper.h

        database/include/Wrappers/DBWrapper.h
        database/include/Wrappers/StorageWrapper.h

        database/src/AmazonS3StorageWrapper.cpp database/src/PostgreDBWrapper.cpp database/src/DataManager.cpp)

target_link_libraries(Proforgia ${AWSSDK_LINK_LIBRARIES})