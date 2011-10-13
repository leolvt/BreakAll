#include <GL/glew.h>
#include <GL/glfw.h>

#include "BreakAll.h"
#include "GameMode.h"

namespace BreakAll 
{

// ========================== //

/**
 * Under this annonymous namespace we store the data needed to control
 * the operation of the game, including the game mode, the screen size, etc.
 */
namespace 
{
    // These control the current status
    bool isInitialized = false;
    int modeCode = 0;
    Mode* currentMode = 0;
    int width = 0;
    int height = 0;
    float aspectRatio = 0;

    // Here we store the available modes
    Mode* gameMode = 0;
};

// ========================== //

/** 
 * initialize - Set up the OpenGL Context, create the window
 * and configure initial game state.
 *
 * Default window size: 800x600
 *
 */
void initialize(int windowWidth, int windowHeight)
{
    // Check if we already have a BreakAll
    if (isInitialized) return;

    // Start at GameMode
    gameMode = new GameMode();
    currentMode = gameMode;
    modeCode = GAME_MODE;
    
    // Initialize GLFW, Open a new Window and Initilize GLEW
    glfwInit();
    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, 1);
    glfwOpenWindow(800,600, 8,8,8,0, 0,0, GLFW_WINDOW);
    glfwSetKeyCallback( BreakAll::keyCallback );
    glfwSetMousePosCallback( BreakAll::mouseCallback );
    glewInit();
    width = 800; height = 600;

    // Define our Projection based by the window aspect 
    glMatrixMode( GL_PROJECTION );
    aspectRatio = (float) width/ (float)height;
    gluOrtho2D(-aspectRatio, aspectRatio,-1,1);
    glMatrixMode( GL_MODELVIEW );

    // Background Color is initially Black
    glClearColor( 0.0, 0.0, 0.0, 0.0 );

    // Mark as initilized
    isInitialized = true;
}

// ========================== //

void terminate()
{
    // Check if we already have a BreakAll
    if (!isInitialized) return;

    // Terminate GLFW. No more fun ;)
    glfwTerminate();

    // Clear Memory
    if (gameMode != 0)
    {
        delete gameMode;
        gameMode = 0;
    }

    // Reset vars
    currentMode = 0;

    // Mark as not initialized
    isInitialized = false;
}

// ========================== //

void run()
{
    // Check if we already have a BreakAll
    if (!isInitialized) return;

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

}

// ========================== //

void changeMode(int NewMode)
{
    // Try to avoid unnecessary work
    if (NewMode == modeCode) return;

    // Change to Game Mode
    if (NewMode == GAME_MODE)
    {
        currentMode = gameMode;
        modeCode = GAME_MODE;
    }
}

// ========================== //

void keyCallback(int Key, int Status)
{
    // Check if we are running and dispatch event to current mode
    if (!isInitialized) return;
    currentMode->onKeyChange(Key, Status);
}

// ========================== //

void mouseCallback(int x, int y)
{
    // Check if we are running 
    if (!isInitialized) return;
    
    // Translate the pixel position to OpenGL 3D position
    float glXpos = ((float)x / (float)width)*2*aspectRatio - aspectRatio;
    float glYpos = ((float)y / (float)height)*2 - 1;

    // Dispatch event to current mode
    currentMode->onMouseChange(glXpos, glYpos);
}

// ========================== //

}; // namespace BreakAll
