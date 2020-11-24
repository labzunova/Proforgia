cmake_minimum_required(VERSION 3.15)
project(Proforgia)

set(CMAKE_CXX_STANDARD 14)

add_executable(Proforgia main.cpp
        database/include/DataManager.h

        database/include/Utils/DBEntities.h
        database/include/Utils/ErrorCodes.h
        database/include/Utils/InputEntities.h
        database/include/Utils/Rights.h

        database/include/Wrappers/DBWrapperRealisations/PostgreDBWrapper.h
        database/include/Wrappers/StorageWrapperRealisations/AmazonS3StorageWrapper.h

        database/include/Wrappers/DBWrapper.h
        database/include/Wrappers/StorageWrapper.h

        database/src/AmazonS3StorageWrapper.cpp database/src/PostgreDBWrapper.cpp database/src/DataManager.cpp)