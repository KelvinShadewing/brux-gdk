if(WIN32)
    set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../winLibs)

endif()
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

message( ${SDL2_INCLUDE_DIRS} )
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
target_link_libraries(brux-gdk squirrel sqstdlib ${SDL2_LIBRARIES} )
if(WIN32)
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

endif()