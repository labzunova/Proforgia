#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "aws-cpp-sdk-core" for configuration "Debug"
set_property(TARGET aws-cpp-sdk-core APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(aws-cpp-sdk-core PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libaws-cpp-sdk-core.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libaws-cpp-sdk-core.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS aws-cpp-sdk-core )
list(APPEND _IMPORT_CHECK_FILES_FOR_aws-cpp-sdk-core "${_IMPORT_PREFIX}/lib/libaws-cpp-sdk-core.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
