#include <GL/glew.h>
#include <GL/glfw.h>

#include "BreakAll.h"
#include "GameMode.h"

// ========================== //

BreakAll::BreakAll()
{
    // Start at GameMode
    this->currentMode = new GameMode();
}

// ========================== //

BreakAll::~BreakAll()
{
    if (this->currentMode != 0)
        delete this->currentMode;
}

// ========================== //

void BreakAll::run()
{
    // Initialize GLFW, Open a new Window and Initilize GLEW
    glfwInit();
    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, 1);
    glfwOpenWindow(800,600, 8,8,8,0, 0,0, GLFW_WINDOW);
    glewInit();

    // Define our Projection based by the window aspect (4:3)
    glMatrixMode( GL_PROJECTION );
    gluOrtho2D(-1.3333,1.3333,-1,1);
    glMatrixMode( GL_MODELVIEW );

    // Background Color
    glClearColor( 0.0, 1.0, 1.0, 1.0 );

    // Main Loop
    bool run = true;
    while (run)
    {
        // Clear
        glClear(GL_COLOR_BUFFER_BIT);

        // Update and draw mode
        currentMode->update();
        currentMode->draw();

        // Check if we should stop
        run= !glfwGetKey( GLFW_KEY_ESC ) &&
            glfwGetWindowParam( GLFW_OPENED );

        // Swap the buffer and sleep, to avoid high FPS and CPU usage
        glfwSwapBuffers();
        glfwSleep(0.02);
    }

    // Terminate GLFW. No more fun ;)
    glfwTerminate();
}

// ========================== //

