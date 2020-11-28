#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "testing-resources" for configuration "Debug"
set_property(TARGET testing-resources APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(testing-resources PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libtesting-resources.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libtesting-resources.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS testing-resources )
list(APPEND _IMPORT_CHECK_FILES_FOR_testing-resources "${_IMPORT_PREFIX}/lib/libtesting-resources.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
