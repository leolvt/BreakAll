# Initial setup
cmake_minimum_required(VERSION 2.6)
project(BreakAll)

# Help cmake find custom modules
set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  "${CMAKE_SOURCE_DIR}/../cmake"
  "${CMAKE_SOURCE_DIR}/../cmake/Modules"
)

# Find the GL libraries we are using
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW REQUIRED)

# Find Font Packages
#find_package(FreeType REQUIRED)
#find_package(OGLFT REQUIRED)

# Find GLM Lib needed for math
find_package(GLM REQUIRED)

# Gather all the libs into one variable
set(BREAKALL_LIBS 
    ${BREAKALL_LIBS} 
    ${OPENGL_LIBRARIES} 
    ${GLFW_LIBRARIES} 
    ${GLEW_LIBRARY}
    #${FREETYPE_LIBRARIES}
    #${OGLFT_LIBRARIES}
)

# Define paths to include and link
include_directories(
    ${PROJECT_SOURCE_DIR}/../include 
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
    #${FREETYPE_INCLUDE_DIR}
    #${OGLFT_INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
)
link_directories(${PROJECT_SOURCE_DIR}/../lib)

# Copy Needed font to build output dir
#file(COPY "content/DejaVuSansMono.ttf" DESTINATION ${CMAKE_BINARY_DIR})

set(BREAKALL_SRC 
    ${BREAKALL_SRC} 
    #paddle.cpp
    #Brick.cpp
	#Ball.cpp
    #Level.cpp
    #GameMode.cpp
    #BreakAll.cpp
    #Util.cpp
    main.cpp
)

set(CMAKE_CXX_FLAGS "-std=c++0x")

add_executable(BreakAll ${BREAKALL_SRC})
target_link_libraries(BreakAll ${BREAKALL_LIBS})
