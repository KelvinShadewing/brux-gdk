# ORIGIN: https://github.com/xbmc/audiodecoder.modplug/blob/Nexus/FindModplug.cmake
#
#
# - Try to find modplug
# Once done this will define
#
# MODPLUG_FOUND - system has libmodplug
# MODPLUG_INCLUDE_DIRS - the libmodplug include directory
# MODPLUG_LIBRARIES - The libmodplug libraries

find_package(PkgConfig)
if(PKG_CONFIG_FOUND)
  pkg_check_modules(PC_MODPLUG libmodplug QUIET)
endif()

find_path(MODPLUG_INCLUDE_DIRS libmodplug/modplug.h
                               PATHS ${PC_MODPLUG_INCLUDEDIR})
find_library(MODPLUG_LIBRARIES NAMES modplug
                               PATHS ${PC_MODPLUG_LIBDIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Modplug REQUIRED_VARS MODPLUG_INCLUDE_DIRS MODPLUG_LIBRARIES)

mark_as_advanced(MODPLUG_INCLUDE_DIRS MODPLUG_LIBRARIES)
