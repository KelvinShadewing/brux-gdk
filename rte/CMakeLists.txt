cmake_minimum_required(VERSION 3.7)

project(brux)
set(CMAKE_CXX_STANDARD 17)

# Set initial variables
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(INSTALL_SUBDIR_BIN "/")

# Define options
option(BUILD_STATIC_LIBS "Link libraries statically whenever possible" OFF)

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
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_net REQUIRED)
include(ProvidePhysFS)
include(ProvideSquirrel)

# If static linking is enabled, link additional libraries
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
  find_package(OGG REQUIRED)
  find_package(FLAC REQUIRED)
  find_package(Modplug REQUIRED)
  find_package(MPG123 REQUIRED)
  find_package(VORBIS REQUIRED)
  find_package(OpusFile REQUIRED)
  target_link_libraries(SDL2::Mixer INTERFACE ${FLAC_LIBRARY} fluidsynth ${MODPLUG_LIBRARIES} ${MPG123_LIBRARIES} ${VORBIS_LIBRARIES} ${OPUSFILE_LIBRARIES} ${OGG_LIBRARIES})
endif()

# Include additional scripts
include(BuildMiniswigWrapper)

# Set include directories
include_directories(${SDL2_INCLUDE_DIRS})
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

# Search for source files and copy the test suite to the output directory
file(GLOB SRCFILES src/api/*.cpp
                   src/brux/*.cpp
                   src/external/*.c
                   src/squirrel/*.cpp
                   src/squirrel/wrapper.cpp
                   src/game/*.cpp
                   src/math2/*.cpp
                   src/math3/*.cpp
                   src/test/game/*.cpp
                   src/test/projection_test/*.cpp
                   src/test/playground/*.cpp)
add_executable(brux ${SRCFILES})
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/test/" DESTINATION "${RUNTIME_OUTPUT_DIR}")

# Link libraries
if(WIN32) # FIXME: Proper way of having the SDL2 libraries copied over to binary on Windows?
  target_link_libraries(brux PUBLIC ${SDL2_LIBRARIES})
  target_link_libraries(brux PUBLIC ${SDL2_IMAGE_LIBRARIES})
  target_link_libraries(brux PUBLIC ${SDL2_GFX_LIBRARIES})
  target_link_libraries(brux PUBLIC ${SDL2_MIXER_LIBRARIES})
  target_link_libraries(brux PUBLIC ${SDL2_NET_LIBRARIES})
else()
  target_link_libraries(brux PUBLIC SDL2)
  target_link_libraries(brux PUBLIC SDL2::Image)
  target_link_libraries(brux PUBLIC SDL2::GFX)
  target_link_libraries(brux PUBLIC SDL2::Mixer)
  target_link_libraries(brux PUBLIC SDL2::Net)
endif()
target_link_libraries(brux PUBLIC LibPhysfs)
target_link_libraries(brux PUBLIC LibSquirrel)
target_link_libraries(brux PUBLIC LibSqstdlib)
