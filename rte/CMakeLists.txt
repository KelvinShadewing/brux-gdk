cmake_minimum_required(VERSION 3.7)
project(rte)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${rte_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_net REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(Squirrel REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
        ${SDL2_MIXER_INCLUDE_DIR}
        ${Squirrel_INCLUDE_DIR})


set(SOURCE_FILES
        audio.cpp
        audio.h
        binds.cpp
        binds.h
        fileio.cpp
        fileio.h
        global.cpp
        global.h
        graphics.cpp
        graphics.h
        input.cpp
        input.h
        main.cpp
        main.h
        maths.cpp
        maths.h
        sprite.cpp
        sprite.h
        text.cpp
        text.h)

configure_file(${CMAKE_SOURCE_DIR}/bin/xylib/core.nut ${CMAKE_BINARY_DIR}/bin/xylib/core.nut COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/bin/xylib/shapes.nut ${CMAKE_BINARY_DIR}/bin/xylib/shapes.nut COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/bin/xylib/tmx.nut ${CMAKE_BINARY_DIR}/bin/xylib/tmx.nut COPYONLY)

add_executable(rte ${SOURCE_FILES})

target_link_libraries(rte ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_NET_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
        ${Squirrel_LIBRARY}
        ${Squirrel_STD_LIBRARY})
