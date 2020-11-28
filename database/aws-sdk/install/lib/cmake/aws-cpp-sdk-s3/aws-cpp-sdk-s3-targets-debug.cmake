#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "aws-cpp-sdk-s3" for configuration "Debug"
set_property(TARGET aws-cpp-sdk-s3 APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(aws-cpp-sdk-s3 PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "aws-cpp-sdk-core"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libaws-cpp-sdk-s3.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libaws-cpp-sdk-s3.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS aws-cpp-sdk-s3 )
list(APPEND _IMPORT_CHECK_FILES_FOR_aws-cpp-sdk-s3 "${_IMPORT_PREFIX}/lib/libaws-cpp-sdk-s3.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
