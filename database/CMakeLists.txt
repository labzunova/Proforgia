set(DATABASE_LIB database_lib)

SET(INCLUDE
        include/DataManager.h

        include/Utils/DBEntities.h
        include/Utils/ErrorCodes.h
        include/Utils/Rights.h

        include/Wrappers/DBWrapperRealisations/PostgreDBWrapper.h
        include/Wrappers/StorageWrapperRealisations/AmazonS3StorageWrapper.h

        include/Wrappers/DBWrapper.h
        include/Wrappers/StorageWrapper.h)


set(SOURCE_FILES
        src/AmazonS3StorageWrapper.cpp
        src/PostgreDBWrapper.cpp
        src/DataManager.cpp
        src/DBEntities.cpp)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

find_package(AWSSDK REQUIRED COMPONENTS s3)

find_package(PostgreSQL REQUIRED)

SET(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS log)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(${INCLUDE})

add_library(${DATABASE_LIB} STATIC ${SOURCE_FILES})
target_link_libraries(${DATABASE_LIB} ${AWSSDK_LINK_LIBRARIES} ${PostgreSQL_LIBRARIES} ${Boost_LIBRARIES})
target_include_directories(${DATABASE_LIB} PRIVATE ${PostgreSQL_INCLUDE_DIRS})