#
# Try to find OGLFT library and include path.
# Once done this will define
#
# OGLFT_FOUND - true/false
# OGLFT_INCLUDE_DIR - Where OGLFT.h is located
# OGLFT_LIBRARIES - libs to link if you need OGLFT
# 

FIND_PATH(OGLFT_INCLUDE_DIR oglft/OGLFT.h
    ${PROJECT_SOURCE_DIR}/../include
    $ENV{OGLFTDIR}/include 
    /usr/local/include
    /usr/local/X11R6/include 
    /usr/X11R6/include 
    /usr/X11/include 
    /usr/include/X11 
    /usr/include 
    /opt/X11/include 
    /opt/include
    DOC "The directory where OGLFT.h resides"
    )

FIND_LIBRARY(OGLFT_LIBRARIES NAMES OGLFT PATHS 
    ${PROJECT_SOURCE_DIR}/../lib
    $ENV{OGLFTDIR}/lib 
    /usr/local/lib
    /usr/local/X11R6/lib
    /usr/X11R6/lib 
    /usr/X11/lib
    /usr/lib/X11
    /usr/lib 
    /opt/X11/lib
    /opt/lib 
    DOC "The OGLFT library"
    )

IF (OGLFT_INCLUDE_PATH)
    IF (OGLFT_LIBRARIES)
        SET( OGLFT_FOUND 1 CACHE STRING "Set to 1 if OGLFT is found, 0 otherwise")
    ELSE (OGLFT_LIBRARIES)
        SET( OGLFT_FOUND 0 CACHE STRING "Set to 1 if OGLFT is found, 0 otherwise")
    ENDIF(OGLFT_LIBRARIES)
ELSE (OGLFT_INCLUDE_PATH)
    SET( OGLFT_FOUND 0 CACHE STRING "Set to 1 if OGLFT is found, 0 otherwise")
ENDIF (OGLFT_INCLUDE_PATH)

MARK_AS_ADVANCED( OGLFT_FOUND )

