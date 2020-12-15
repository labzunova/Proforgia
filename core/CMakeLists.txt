set(CORE_LIB core_lib)

set(HEADER_FILES
        include/Worker.h
        include/Handler.h
        include/page/PageCustomer.h
        include/page/PageUser.h
        include/page/PageManager.h
        include/activity/ActivityManager.h
        include/activity/ActivityCustomer.h
        include/activity/ActivityUser.h
        include/HttpResponse.h
#        include/external_api/View.h
#        include/entities/entities.h
        )

set(INCLUDE
        include/activity
        include/entities
        include/external_api
        include/page
        include
        src
        )

set(SOURCE_FILES
        src/Worker.cpp
        src/Handler.cpp
        src/page/PageCustomer.cpp
        src/page/PageUser.cpp
        src/activity/ActivityManager.cpp
        src/activity/ActivityCustomer.cpp
        src/activity/ActivityUser.cpp
        src/HttpResponse.cpp
        )

set(SOURCE_FILES_TESTS
#        ../tests/core/gmock_tests.cpp
#        ../tests/core/http_response_tests.cpp
#        ../tests/core/page_tests.cpp
        ../tests/core/worker_tests.cpp
        )

include_directories("${PROJECT_SOURCE_DIR}/core")

SET(Boost_USE_STATIC_LIBS ON)
FIND_PACKAGE(Boost REQUIRED COMPONENTS log)
find_package(GTest)
include_directories(${Boost_INCLUDE_DIRS})

add_library(${CORE_LIB} STATIC ${SOURCE_FILES})
#target_link_libraries(${CORE_LIB} ${Boost_LIBRARIES} TemplatesEngine)
target_link_libraries(${CORE_LIB} ${Boost_LIBRARIES} database_lib TemplatesEngine)
target_include_directories(${CORE_LIB} PUBLIC ${INCLUDE})

add_executable(tests_core ${SOURCE_FILES_TESTS})
#add "rt" flag  if not on mac
target_link_libraries(tests_core gtest gmock gtest_main -ldl pthread ${CORE_LIB})

