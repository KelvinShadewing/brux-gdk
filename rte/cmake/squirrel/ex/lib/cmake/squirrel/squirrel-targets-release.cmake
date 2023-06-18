#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "squirrel::squirrel" for configuration "Release"
set_property(TARGET squirrel::squirrel APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(squirrel::squirrel PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libsquirrel.so.0.0.0"
  IMPORTED_SONAME_RELEASE "libsquirrel.so.0"
  )

list(APPEND _IMPORT_CHECK_TARGETS squirrel::squirrel )
list(APPEND _IMPORT_CHECK_FILES_FOR_squirrel::squirrel "${_IMPORT_PREFIX}/lib/libsquirrel.so.0.0.0" )

# Import target "squirrel::squirrel_static" for configuration "Release"
set_property(TARGET squirrel::squirrel_static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(squirrel::squirrel_static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libsquirrel_static.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS squirrel::squirrel_static )
list(APPEND _IMPORT_CHECK_FILES_FOR_squirrel::squirrel_static "${_IMPORT_PREFIX}/lib/libsquirrel_static.a" )

# Import target "squirrel::sqstdlib" for configuration "Release"
set_property(TARGET squirrel::sqstdlib APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(squirrel::sqstdlib PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libsqstdlib.so.0.0.0"
  IMPORTED_SONAME_RELEASE "libsqstdlib.so.0"
  )

list(APPEND _IMPORT_CHECK_TARGETS squirrel::sqstdlib )
list(APPEND _IMPORT_CHECK_FILES_FOR_squirrel::sqstdlib "${_IMPORT_PREFIX}/lib/libsqstdlib.so.0.0.0" )

# Import target "squirrel::sqstdlib_static" for configuration "Release"
set_property(TARGET squirrel::sqstdlib_static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(squirrel::sqstdlib_static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libsqstdlib_static.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS squirrel::sqstdlib_static )
list(APPEND _IMPORT_CHECK_FILES_FOR_squirrel::sqstdlib_static "${_IMPORT_PREFIX}/lib/libsqstdlib_static.a" )

# Import target "squirrel::interpreter" for configuration "Release"
set_property(TARGET squirrel::interpreter APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(squirrel::interpreter PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/sq"
  )

list(APPEND _IMPORT_CHECK_TARGETS squirrel::interpreter )
list(APPEND _IMPORT_CHECK_FILES_FOR_squirrel::interpreter "${_IMPORT_PREFIX}/bin/sq" )

# Import target "squirrel::interpreter_static" for configuration "Release"
set_property(TARGET squirrel::interpreter_static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(squirrel::interpreter_static PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/sq_static"
  )

list(APPEND _IMPORT_CHECK_TARGETS squirrel::interpreter_static )
list(APPEND _IMPORT_CHECK_FILES_FOR_squirrel::interpreter_static "${_IMPORT_PREFIX}/bin/sq_static" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
