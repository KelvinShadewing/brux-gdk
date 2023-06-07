cmake_minimum_required(VERSION 3.7)

project(brux)
set(CMAKE_CXX_STANDARD 17)

# Set initial variables

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(INSTALL_SUBDIR_BIN "/")

# Define options

option(BUILD_STATIC_LIBS "Link libraries statically whenever possible" OFF)

find_package(SDL2_mixer QUIET)

# Enable USE_SDL2_MIXER by default if SDL2_mixer is found

if (SDL2_mixer_FOUND)
  option(USE_SDL2_MIXER "Use SDL2 to provide audio support" ON)
else()
  option(USE_SDL2_MIXER "Use SDL2 to provide audio support" OFF)
  message(STATUS "Could NOT find SDL2 Mixer, disabling audio support")
endif()

# Please don't disable this unless you have a specific reason to.
# fastfill is significantly faster than the original algorithm, as it's O(1) instead of O(n).

if (USE_SDL2_MIXER)
  option(USE_FASTFILL "Use an O(1) algorithm for replacing unloaded sounds with new sounds instead of the original O(n) algorithm" ON)
endif()

if (USE_SDL2_MIXER)
  set(AUDIO_SOURCE src/audio/audio_sdl2.cpp)
else()
  set(AUDIO_SOURCE src/audio/audio_none.cpp)
endif()

# preprocess config.hpp, used for optional libraries

configure_file(src/config.hpp.in config.hpp)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

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

# Prefer static linking, whenever possible

if(BUILD_STATIC_LIBS)
  set(CMAKE_FIND_LIBRARY_SUFFIXES .lib .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
endif()

# Required includes

include(ExternalProject)
include(CheckSymbolExists)

# Find/provide packages

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_gfx REQUIRED)

include(ProvidePhysFS)
include(ProvideSquirrel)

# If static linking is enabled, link additional libraries
# Also, look at all of the dependencies it uses. This is one of the reasons why the portability API exists.

if(BUILD_STATIC_LIBS)
  # SDL2::Image libraries
  find_package(JPEG REQUIRED)
  find_package(PNG REQUIRED)
  find_package(TIFF REQUIRED)
  find_package(LZMA REQUIRED)
  find_package(zstd REQUIRED)
  find_package(JBIG REQUIRED)
  find_package(Deflate REQUIRED)
  find_package(WebP REQUIRED)
  target_link_libraries(SDL2::Image INTERFACE ${JPEG_LIBRARIES} ${PNG_LIBRARIES} ${TIFF_LIBRARIES} ${LZMA_LIBRARIES} ${zstd_LIBRARIES} ${JBIG_LIBRARIES} ${Deflate_LIBRARIES} ${WebP_LIBRARIES})

  # SDL2::Mixer libraries

  if (USE_SDL2_MIXER)
    find_package(OGG REQUIRED)
    find_package(FLAC REQUIRED)
    find_package(Modplug REQUIRED)
    find_package(MPG123 REQUIRED)
    find_package(VORBIS REQUIRED)
    find_package(OpusFile REQUIRED)
    target_link_libraries(SDL2::Mixer INTERFACE ${FLAC_LIBRARY} fluidsynth ${MODPLUG_LIBRARIES} ${MPG123_LIBRARIES} ${VORBIS_LIBRARIES} ${OPUSFILE_LIBRARIES} ${OGG_LIBRARIES})
  endif()
endif()

# Include additional scripts
include(BuildMiniswigWrapper)

# Set include directories
include_directories(${SDL2_INCLUDE_DIRS})
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

# Search for source files and copy the test suite to the output directory
file(GLOB SRCFILES src/api/*.cpp
                   src/brux/*.cpp
                   ${AUDIO_SOURCE}
                   src/external/*.c
                   src/squirrel/*.cpp
                   src/squirrel/wrapper.cpp)
add_executable(brux ${SRCFILES})
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/test/" DESTINATION "${RUNTIME_OUTPUT_DIR}")

# Link libraries

if(WIN32) # FIXME: Proper way of having the SDL2 libraries copied over to binary on Windows?
  target_link_libraries(brux PUBLIC ${SDL2_LIBRARIES})
  target_link_libraries(brux PUBLIC ${SDL2_IMAGE_LIBRARIES})
  target_link_libraries(brux PUBLIC ${SDL2_GFX_LIBRARIES})

  if (USE_SDL2_MIXER)
    target_link_libraries(brux PUBLIC ${SDL2_MIXER_LIBRARIES})
  endif()
else()
  target_link_libraries(brux PUBLIC SDL2)
  target_link_libraries(brux PUBLIC SDL2::Image)
  target_link_libraries(brux PUBLIC SDL2::GFX)

  if (USE_SDL2_MIXER)
    target_link_libraries(brux PUBLIC SDL2::Mixer)
  endif()
endif()

target_link_libraries(brux PUBLIC LibPhysfs)
target_link_libraries(brux PUBLIC LibSquirrel)
target_link_libraries(brux PUBLIC LibSqstdlib)
