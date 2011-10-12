#
# Try to find FreeType 2 library and include path.
# Once done this will define
#
# FREETYPE_FOUND - true/false
# FREETYPE_INCLUDE_DIR - Where freetype/freetype.h is located
# FREETYPE_LIBRARIES - libs to link if you need FreeType
# 

FIND_PATH(FREETYPE_INCLUDE_DIR freetype/freetype.h
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/freetype2
    $ENV{FREETYPEDIR}/include 
    /usr/include/freetype2
    /usr/local/include
    /usr/local/include/freetype2
    /usr/local/X11R6/include 
    /usr/X11R6/include 
    /usr/X11/include 
    /usr/include/X11 
    /usr/include 
    /opt/X11/include 
    /opt/include
    /opt/include/freetype2
    DOC "The directory where freetype/freetype.h resides"
    )

FIND_LIBRARY(FREETYPE_LIBRARIES NAMES freetype PATHS 
    ${PROJECT_SOURCE_DIR}/lib
    $ENV{FREETYPEDIR}/lib 
    /usr/local/lib
    /usr/local/X11R6/lib
    /usr/X11R6/lib 
    /usr/X11/lib
    /usr/lib/X11
    /usr/lib 
    /opt/X11/lib
    /opt/lib 
    DOC "The FreeType library"
    )

IF (FREETYPE_INCLUDE_PATH)
    IF (FREETYPE_LIBRARIES)
        SET( FREETYPE_FOUND 1 CACHE STRING "Set to 1 if FreeType is found, 0 otherwise")
    ELSE (FREETYPE_LIBRARIES)
        SET( FREETYPE_FOUND 0 CACHE STRING "Set to 1 if FreeType is found, 0 otherwise")
    ENDIF(FREETYPE_LIBRARIES)
ELSE (FREETYPE_INCLUDE_PATH)
    SET( FREETYPE_FOUND 0 CACHE STRING "Set to 1 if FreeType is found, 0 otherwise")
ENDIF (FREETYPE_INCLUDE_PATH)

MARK_AS_ADVANCED( FREETYPE_FOUND )

