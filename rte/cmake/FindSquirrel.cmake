# - Try to find Squirrel
# Once done this will define
#
#  Squirrel_FOUND - system has Squirrel
#  Squirrel_INCLUDE_DIR - the include directory
#  Squirrel_LIBRARY - The Squirrel library
#  Squirrel_STD_LIBRARY - The Squirrel std library


FIND_PATH(Squirrel_INCLUDE_DIR squirrel.h 
        HINTS
        PATH_SUFFIXES squirrel
		PATHS ${Squirrel_DIR}
		)

FIND_LIBRARY(Squirrel_LIBRARY 
		NAMES squirrel
		PATH_SUFFIXES squirrel
		PATHS ${Squirrel_DIR}
		)

FIND_LIBRARY(Squirrel_STD_LIBRARY
		NAMES sqstdlib
		PATH_SUFFIXES squirrel
		PATHS ${Squirrel_DIR}
		)

MARK_AS_ADVANCED(Squirrel_INCLUDE_DIR Squirrel_LIBRARY)

IF(Squirrel_INCLUDE_DIR AND Squirrel_LIBRARY)
    SET(Squirrel_FOUND TRUE)
ELSE(Squirrel_INCLUDE_DIR AND Squirrel_LIBRARY)
    SET(Squirrel_FOUND FALSE)
ENDIF(Squirrel_INCLUDE_DIR AND Squirrel_LIBRARY)