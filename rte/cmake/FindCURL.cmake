# - FindCURL.cmake
# Find the native CURL includes and libraries
#
# CURL_INCLUDE_DIRS - where to find curl/curl.h, etc.
# CURL_LIBRARIES    - List of libraries when using CURL.
# CURL_FOUND        - True if CURL is found.

if(CURL_INCLUDE_DIR AND CURL_LIBRARY)
    # Already in cache, be silent
    set(CURL_FIND_QUIETLY TRUE)
endif()

find_path(CURL_INCLUDE_DIR curl/curl.h)

# On Windows, libcurl may be named curl, libcurl, or curllib (static).
find_library(CURL_LIBRARY NAMES curl libcurl curllib curllib_static)

# Handle the QUIETLY and REQUIRED arguments and set CURL_FOUND
# to TRUE if all listed variables are TRUE.
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CURL DEFAULT_MSG CURL_LIBRARY CURL_INCLUDE_DIR)

if(CURL_FOUND)
    set(CURL_LIBRARIES ${CURL_LIBRARY})
    set(CURL_INCLUDE_DIRS ${CURL_INCLUDE_DIR})
endif()
