#include <GL/glew.h>
#include <GL/glfw.h>

#include "Engine.h"

// ============================================== //

namespace Engine
{

// ============================================== //

/*
 * Store "private globals"
 */
namespace
{
    OnKeyEvent keyCallback = 0;
};

// ============================================== //

void GLFWCALL handleKeys( int key, int action )
{
    if (keyCallback == 0) return;
    Engine::Key k;

    switch (key)
    {
        case GLFW_KEY_ESC:
            k = Engine::KEY_ESC;
            break;
    }

    keyCallback(k, (Engine::KeyState)action);
}


// ============================================== //

void Init()
{
    // Initialize OpenGL Framework
    glfwInit();
    glfwDisable( GLFW_AUTO_POLL_EVENTS );
}

// ============================================== //

void Terminate()
{
    // Terminate OpenGL Framework
    glfwTerminate();
}

// ============================================== //

/**
 *  Open a window with the given size and title
 */
void OpenWindow(int width, int height, std::string title)
{
    // Create a Non Resiseable Window
    glfwOpenWindowHint( GLFW_WINDOW_NO_RESIZE, true );
    glEnable(GL_DEPTH_TEST);

    // Define the title of the window
    glfwSetWindowTitle( title.c_str() );

    // The other parameters define color, alpha, depth and stencil bits
    glfwOpenWindow( width, height,  8, 8, 8,  8, 8, 0, GLFW_WINDOW);
    glfwSetKeyCallback( &handleKeys );
}

// ============================================== //

/**
 *  Open a Full Screen window with the given size and title
 */
void OpenFullScreenWindow(int width, int height, std::string title)
{
    // Define the title of the window
    glfwSetWindowTitle( title.c_str() );

    // The other parameters define color, alpha, depth and stencil bits
    glfwOpenWindow( width, height,  8, 8, 8,  8, 8, 0, GLFW_FULLSCREEN);
    glfwSetKeyCallback( &handleKeys );
}

// ============================================== //

/**
 * Swap the Video Card Buffers, effectively showing what was drawn
 * into the screen.
 */
void SwapBuffers()
{
    glfwSwapBuffers();
}

// ============================================== //

/**
 * Get Ellapsed time in seconds since the initialization or
 * since the timer was set
 */
double GetTime()
{
    return glfwGetTime();
}

// ============================================== //

/**
 * Set the timer to a specific time
 */
void SetTime(double time)
{
    glfwSetTime(time);
}

// ============================================== //

/**
 * Poll for events such as key press or mouse events
 */
void PollEvents()
{
    glfwPollEvents();
}

// ============================================== //

/**
 * Check if the Window is currently open
 */
bool IsWindowOpen()
{
    return glfwGetWindowParam( GLFW_OPENED ) == GL_TRUE;
}

// ============================================== //

/**
 * Clear the current buffer
 */
void ClearScreen()
{
    //glClearColor(0.3, 0.3, 0.3, 0.3);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// ============================================== //

void SetKeyCallback(OnKeyEvent e)
{
    keyCallback = e;
}

// ============================================== //

// ============================================== //

}; /* namespace Engine */
