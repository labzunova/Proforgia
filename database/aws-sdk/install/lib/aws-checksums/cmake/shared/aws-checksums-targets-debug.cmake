#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "AWS::aws-checksums" for configuration "Debug"
set_property(TARGET AWS::aws-checksums APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(AWS::aws-checksums PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libaws-checksums.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libaws-checksums.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS AWS::aws-checksums )
list(APPEND _IMPORT_CHECK_FILES_FOR_AWS::aws-checksums "${_IMPORT_PREFIX}/lib/libaws-checksums.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
