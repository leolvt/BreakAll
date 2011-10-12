# Initial setup
cmake_minimum_required(VERSION 2.6)
project(Breakout)

# Help cmake find custom modules
set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  "${CMAKE_SOURCE_DIR}/cmake"
  "${CMAKE_SOURCE_DIR}/cmake/Modules"
)

# Find the GL libraries we are using
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW REQUIRED)

# Find Font Packages
find_package(FreeType REQUIRED)
find_package(OGLFT REQUIRED)

# Gather all the libs into one variable
set(BREAKOUT_LIBS 
    ${BREAKOUT_LIBS} 
    ${OPENGL_LIBRARIES} 
    ${GLFW_LIBRARIES} 
    ${GLEW_LIBRARY}
    ${FREETYPE_LIBRARIES}
    ${OGLFT_LIBRARIES}
)

# Define paths to include and link
include_directories(
    ${PROJECT_SOURCE_DIR}/include 
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
    ${FREETYPE_INCLUDE_DIR}
    ${OGLFT_INCLUDE_DIR}
)
link_directories(${PROJECT_SOURCE_DIR}/lib)

# Add our source dir to cmake
add_subdirectory(src)
