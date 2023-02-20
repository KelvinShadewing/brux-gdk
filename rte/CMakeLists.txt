cmake_minimum_required(VERSION 3.7)

project(brux)
set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(INSTALL_SUBDIR_BIN "/")

# Set runtime output directory for Visual Studio and others.
if(MSVC)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "Debug")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "Release")

  # FIXME: Proper detection of whether Debug/Release directory should be used?
  set(RUNTIME_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}")
else()
  set(RUNTIME_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endif()
set(CMAKE_INSTALL_PREFIX "${RUNTIME_OUTPUT_DIR}")

include(ExternalProject)
include(CheckSymbolExists)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_gfx REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_net REQUIRED)
include(ProvidePhysFS)
include(ProvideSquirrel)

# Miniswig is supported on Linux.
if(UNIX)
  include(BuildMiniswigWrapper)
endif()

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(src)

file(GLOB SRCFILES src/api/*.cpp src/brux/*.cpp src/external/*.c src/squirrel/*.cpp src/squirrel/wrapper.cpp)
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/test/" DESTINATION "${RUNTIME_OUTPUT_DIR}")
add_executable(brux ${SRCFILES})

target_link_libraries(brux PUBLIC ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_GFX_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${SDL2_NET_LIBRARIES})
target_link_libraries(brux PUBLIC LibPhysfs)
target_link_libraries(brux PUBLIC LibSquirrel)
target_link_libraries(brux PUBLIC LibSqstdlib)
