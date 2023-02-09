add_subdirectory(external/miniswig)
add_custom_command(
  OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/squirrel/wrapper.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/squirrel/wrapper.hpp
  COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR} && ${CMAKE_CXX_COMPILER}
  ARGS -x "c++" -E -CC
       -DBRUX_API_GEN src/api/api.hpp
       -o ${CMAKE_CURRENT_BINARY_DIR}/miniswig.tmp
       -Isrc
  COMMAND cd ${CMAKE_CURRENT_BINARY_DIR} && external/miniswig/miniswig
  ARGS --input miniswig.tmp
       --input-hpp api/api.hpp
       --output-cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/squirrel/wrapper.cpp
       --output-hpp ${CMAKE_CURRENT_SOURCE_DIR}/src/squirrel/wrapper.hpp
       --module brux
       --select-namespace BruxAPI
  DEPENDS external/miniswig/miniswig
  IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/src/api/api.hpp
)
add_custom_target(squirrel_wrapper ALL
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/squirrel/wrapper.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/squirrel/wrapper.hpp
)
