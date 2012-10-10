# Initial setup
cmake_minimum_required(VERSION 2.6)
project(BreakAll)

# Help cmake find custom modules
set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  "${CMAKE_SOURCE_DIR}/../cmake"
)

# Find the libraries we are using
find_package(OpenGL REQUIRED)
find_package(SFML 2 REQUIRED COMPONENTS window system graphics)

# Gather all the libs into one variable
set(BREAKALL_LIBS
    ${BREAKALL_LIBS}
    ${OPENGL_LIBRARIES}
    ${SFML_LIBRARIES}
)

# Define paths to include and link
include_directories(
    ${PROJECT_SOURCE_DIR}/../include
    ${OPENGL_INCLUDE_DIR}
    ${SFML_INCLUDE_DIR}
)
link_directories(${PROJECT_SOURCE_DIR}/../lib)

# List the project source files
set(BREAKALL_SRC
    ${BREAKALL_SRC}
    GameScreen.cpp
    BreakAll.cpp
    main.cpp
)

# Set some Compiler Flags
set(CMAKE_CXX_FLAGS "-std=c++0x")

# Declare the executable with the  used libraries
add_executable(BreakAll ${BREAKALL_SRC})
target_link_libraries(BreakAll ${BREAKALL_LIBS})
