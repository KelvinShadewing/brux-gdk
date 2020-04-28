cmake_minimum_required(VERSION 3.10)

# set the project name
if(WIN32)
    include(FetchContent)
    FetchContent_Declare(
            squirrelstf
            GIT_REPOSITORY https://github.com/albertodemichelis/squirrel.git
            GIT_TAG        master
    )
    FetchContent_MakeAvailable(squirrelstf)
    include_directories(${squirrel_SOURCE_DIR}/include)
endif()
project(brux-gdk)

# add the executable
# add_executable(Tutorial tutorial.cxx)

add_subdirectory(rte)