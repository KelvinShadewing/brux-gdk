# ORIGIN: https://github.com/ufz/tiff/blob/master/cmake/Modules/FindJBIG.cmake
#
#
# - Find JBIG-KIT
# Find the native JBIG-KIT includes and library.
# Once done this will define
#
#  JBIG_INCLUDE_DIRS - where to find jbig.h and the required dependencies
#  JBIG_LIBRARIES    - list of libraries when using JBIG-KIT
#  JBIG_FOUND        - true if JBIG-KIT found
#
#  JBIG_VERSION_STRING - The version of JBIG-KIT found (x.y)
#  JBIG_VERSION_MAJOR  - The major version of JBIG-KIT
#  JBIG_VERSION_MINOR  - The minor version of JBIG-KIT
#
# An includer may set JBIG_ROOT to a JBIG-KIT installation root to tell
# this module where to look.
#
#=============================================================================
# Edgar Velázquez-Armendáriz, Cornell University (cs.cornell.edu - eva5)
# Distributed under the OSI-approved MIT License (the "License")
# 
# Copyright (c) 2011 Program of Computer Graphics, Cornell University
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#=============================================================================

include(FindPackageHandleStandardArgs)

set(_JBIG_SEARCHES)

# Search JBIG_ROOT first if it is set.
if(JBIG_ROOT)
  set(_JBIG_SEARCHES PATHS ${JBIG_ROOT} NO_DEFAULT_PATH)
endif()

set(JBIG_NAMES ${JBIG_NAMES} jbig)

find_path(JBIG_INCLUDE_DIR NAMES jbig.h        ${_JBIG_SEARCHES} PATH_SUFFIXES include)
find_library(JBIG_LIBRARY  NAMES ${JBIG_NAMES} ${_JBIG_SEARCHES} PATH_SUFFIXES lib)

mark_as_advanced(JBIG_LIBRARY JBIG_INCLUDE_DIR)

# Version detection based on the default FindZLIB.cmake module
if(JBIG_INCLUDE_DIR AND EXISTS "${JBIG_INCLUDE_DIR}/jbig.h")
  file(STRINGS "${JBIG_INCLUDE_DIR}/jbig.h" JBIG_H REGEX "^#define JBG_VERSION[ \\t]+\"[^\"]*\"$")

  string(REGEX REPLACE "^.*JBG_VERSION[ \\t]+\"([0-9]+).*$" "\\1" JBIG_VERSION_MAJOR "${JBIG_H}")
  string(REGEX REPLACE "^.*JBG_VERSION[ \\t]+\"[0-9]+\\.([0-9]+).*$" "\\1" JBIG_VERSION_MINOR  "${JBIG_H}")
  set(JBIG_VERSION_STRING "${JBIG_VERSION_MAJOR}.${JBIG_VERSION_MINOR}")
  
  # only append a PATCH version if it exists:
  set(JBIG_VERSION_PATCH "")
  if("${JBIG_H}" MATCHES "^.*JBG_VERSION[ \\t]+\"[0-9]+\\.[0-9]+\\.([0-9]+).*$")
    set(JBIG_VERSION_PATCH  "${CMAKE_MATCH_1}")
    set(JBIG_VERSION_STRING "${JBIG_VERSION_STRING}.${JBIG_VERSION_PATCH}")
  endif()  
endif()

# handle the QUIETLY and REQUIRED arguments and set JBIG_FOUND to TRUE if 
# all listed variables are TRUE
FIND_PACKAGE_HANDLE_STANDARD_ARGS(JBIG REQUIRED_VARS JBIG_LIBRARY JBIG_INCLUDE_DIR
                                       VERSION_VAR JBIG_VERSION_STRING)

if(JBIG_FOUND)
  set(JBIG_LIBRARIES ${JBIG_LIBRARY})
  set(JBIG_INCLUDE_DIRS ${JBIG_INCLUDE_DIR})
endif()
