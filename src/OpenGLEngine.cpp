#include <GL/glew.h>
#include <GL/glfw.h>

#include "OpenGLEngine.h"

// ============================================== //

OpenGLEngine::OpenGLEngine()
{
    // Initialize OpenGL Framework
    glfwInit();
}

// ============================================== //

OpenGLEngine::~OpenGLEngine()
{
    // Terminate OpenGL Framework
    glfwTerminate();
}

// ============================================== //

/**
 *  Open a window with the given size and title
 */
void OpenGLEngine::OpenWindow(int width, int height, std::string title)
{
    // Create a Non Resiseable Window
    glfwOpenWindowHint( GLFW_WINDOW_NO_RESIZE, true );
    glEnable(GL_DEPTH_TEST);

    // Define the title of the window
    glfwSetWindowTitle( title.c_str() );

    // The other parameters define color, alpha, depth and stencil bits
    glfwOpenWindow( width, height,  8, 8, 8,  8, 8, 0, GLFW_WINDOW);
}

// ============================================== //

/**
 *  Open a Full Screen window with the given size and title
 */
void OpenGLEngine::OpenFullScreenWindow(int width, int height, std::string title)
{
    // Define the title of the window
    glfwSetWindowTitle( title.c_str() );

    // The other parameters define color, alpha, depth and stencil bits
    glfwOpenWindow( width, height,  8, 8, 8,  8, 8, 0, GLFW_FULLSCREEN);
}

// ============================================== //

/**
 * Swap the Video Card Buffers, effectively showing what was drawn 
 * into the screen.
 */
void OpenGLEngine::SwapBuffers()
{
    glfwSwapBuffers();
}

// ============================================== //

/**
 * Get Ellapsed time in seconds since the initialization or 
 * since the timer was set
 */
double OpenGLEngine::GetTime()
{
    return glfwGetTime();
}

// ============================================== //

/**
 * Set the timer to a specific time
 */
void OpenGLEngine::SetTime(double time)
{
    glfwSetTime(time);
}

// ============================================== //

/**
 * Clear the current buffer
 */
void OpenGLEngine::ClearScreen()
{
    //glClearColor(0.3, 0.3, 0.3, 0.3);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// ============================================== //

// ============================================== //

// ============================================== //
