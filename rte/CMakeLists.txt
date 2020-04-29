if (WIN32 AND NOT MINGW)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/winLibs/")
    include_directories(${PROJECT_SOURCE_DIR}/winLibs/include)
endif ()
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
if (NOT WIN32)
    find_package(SDL2_image REQUIRED)
    include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
    find_package(SDL2_net REQUIRED)
    include_directories(${SDL2_NET_INCLUDE_DIRS})
    find_package(SDL2_mixer REQUIRED)
    include_directories(${SDL2_MIXER_INCLUDE_DIRS})
    find_package(SDL2_gfx REQUIRED)
    include_directories(${SDL2_GFX_INCLUDE_DIRS})
endif ()
SET(brux_gtk_sources
        audio.cpp
        binds.cpp
        cJSON.c
        core.cpp
        fileio.cpp
        global.cpp
        graphics.cpp
        input.cpp
        main.cpp
        maths.cpp
        shapes.cpp
        sprite.cpp
        text.cpp
        tile.cpp
        tinyxml2.cpp
        tmap.cpp
        )

add_executable(brux-gdk ${brux_gtk_sources})

if (WIN32 OR MINGW)
    if (MINGW)
        target_link_libraries(brux-gdk squirrel::squirrel_static squirrel::sqstdlib_static SDL2::SDL2 SDL2::SDL2main ${SDL2_IMAGE_LIBRARIES} ${SDL2_NET_LIBRARIES} ${SDL2_GFX_LIBRARIES} ${SDL2_MIXER_LIBRARIES} -lmingw32 -mwindows)
    else ()
        target_link_libraries(brux-gdk squirrel::squirrel_static squirrel::sqstdlib_static ${SDL2_LIBRARIES})
    endif ()
    if(NOT DEFINED ENV{TRAVIS})
        if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
            add_custom_command(TARGET brux-gdk POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/winLibs/lib/x64" $<TARGET_FILE_DIR:brux-gdk>
                    COMMAND ${CMAKE_COMMAND} -E copy_directory "${squirrel_BINARY_DIR}/bin" $<TARGET_FILE_DIR:brux-gdk>
                    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/bin" $<TARGET_FILE_DIR:brux-gdk>
                    )
        else ()
            add_custom_command(TARGET brux-gdk POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/winLibs/lib/x86" $<TARGET_FILE_DIR:brux-gdk>
                    COMMAND ${CMAKE_COMMAND} -E copy_directory "${squirrel_BINARY_DIR}/bin" $<TARGET_FILE_DIR:brux-gdk>
                    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/bin" $<TARGET_FILE_DIR:brux-gdk>
                    )
        endif ()
    endif ()
endif ()
add_definitions(-DSDL_MAIN_HANDLED)
