cmake_minimum_required(VERSION 3.10)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/" CACHE STRING "" FORCE)
# set the project name
if (WIN32 AND NOT MINGW)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/winLibs" CACHE STRING "" FORCE)
    include_directories(${PROJECT_SOURCE_DIR}/winLibs/include)
endif ()
include(FetchContent)
FetchContent_Declare(
        squirrelstf
        GIT_REPOSITORY https://github.com/albertodemichelis/squirrel.git
        GIT_TAG master
)
FetchContent_MakeAvailable(squirrelstf)
include_directories(${squirrel_SOURCE_DIR}/include)
FetchContent_Declare(
        chipmonk2d
        GIT_REPOSITORY https://github.com/slembcke/Chipmunk2D.git
        GIT_TAG master
)
FetchContent_MakeAvailable(chipmonk2d)
include_directories(${chipmonk2d_SOURCE_DIR}/include/chipmunk)

project(brux-gdk)

# add the executable
# add_executable(Tutorial tutorial.cxx)

add_subdirectory(rte)