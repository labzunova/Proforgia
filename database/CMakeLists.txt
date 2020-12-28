set(DATABASE_LIB database_lib)

set(SOURCE_FILES
        src/AmazonS3StorageWrapper.cpp
        src/PostgreDBWrapper.cpp
        src/DataManager.cpp
        src/DBEntities.cpp)

set(INCLUDE
        include/Utils
        include/Wrappers
        include)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)
find_package(AWSSDK REQUIRED COMPONENTS s3)
find_package(PostgreSQL REQUIRED)
SET(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS log)
include_directories(${Boost_INCLUDE_DIRS})


add_library(${DATABASE_LIB} STATIC ${SOURCE_FILES})
target_link_libraries(${DATABASE_LIB} ${AWSSDK_LINK_LIBRARIES} ${PostgreSQL_LIBRARIES} ${Boost_LIBRARIES})
target_include_directories(${DATABASE_LIB} PUBLIC ${PostgreSQL_INCLUDE_DIRS} ${INCLUDE})

#----------------------------------------tests---------------------------------------------#
set(SOURCE_FILES_TESTS
        ../tests/database/postgres_wrapper_tests.cpp)

add_executable(tests_database ${SOURCE_FILES_TESTS})
target_link_libraries(tests_database gtest gmock gtest_main -ldl pthread ${DATABASE_LIB})

#----------------------------------------end-tests---------------------------------------------#