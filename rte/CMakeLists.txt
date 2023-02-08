cmake_minimum_required(VERSION 3.7)

project(brux)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_gfx REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_net REQUIRED)
find_package(PhysFS REQUIRED)

include(ExternalProject)
include(ProvideSquirrel)

include(BuildMiniswigWrapper)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${PHYSFS_INCLUDE_DIR})
include_directories(src)

file(GLOB SRCFILES src/api/*.cpp src/brux/*.cpp src/external/*.c src/squirrel/*.cpp)
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/test/" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
add_executable(brux ${SRCFILES})

target_link_libraries(brux PUBLIC ${SDL2_LIBRARIES} SDL2_image SDL2_gfx SDL2_mixer SDL2_net)
target_link_libraries(brux PUBLIC ${PHYSFS_LIBRARY})
target_link_libraries(brux PUBLIC LibSquirrel)
target_link_libraries(brux PUBLIC LibSqstdlib)
