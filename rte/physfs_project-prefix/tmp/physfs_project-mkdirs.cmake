# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/kelvin/Code/brux/rte/external/physfs"
  "/home/kelvin/Code/brux/rte/physfs_project-prefix/src/physfs_project-build"
  "/home/kelvin/Code/brux/rte/physfs_project-prefix"
  "/home/kelvin/Code/brux/rte/physfs_project-prefix/tmp"
  "/home/kelvin/Code/brux/rte/physfs_project-prefix/src/physfs_project-stamp"
  "/home/kelvin/Code/brux/rte/physfs_project-prefix/src"
  "/home/kelvin/Code/brux/rte/physfs_project-prefix/src/physfs_project-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/kelvin/Code/brux/rte/physfs_project-prefix/src/physfs_project-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/kelvin/Code/brux/rte/physfs_project-prefix/src/physfs_project-stamp${cfgdir}") # cfgdir has leading slash
endif()
