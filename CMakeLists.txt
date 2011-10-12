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
find_package(GLFW REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

# Add our source dir to cmake
add_subdirectory(src)
