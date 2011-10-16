#include <set>

#include "BreakAll.h"
#include "Mode.h"
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
    bool running = false;
    std::set<int> pressedKeys;

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

    // Initialize GLFW, Open a new Window and Initilize GLEW
    glfwInit();
    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, 1);
    glfwOpenWindow(windowWidth,windowHeight, 8,8,8,0, 0,0, GLFW_WINDOW);
    glfwSetKeyCallback( BreakAll::keyCallback );
    glfwSetMousePosCallback( BreakAll::mouseCallback );
    glewInit();
    width = windowWidth; height = windowHeight;

    // Define our Projection based by the window aspect 
    glMatrixMode( GL_PROJECTION );
    aspectRatio = (float) width/ (float)height;
    gluOrtho2D(-aspectRatio, aspectRatio,-1,1);
    glMatrixMode( GL_MODELVIEW );

    // Start at GameMode
    Area totalArea = {1, aspectRatio, -1, -aspectRatio};
    gameMode = new GameMode(totalArea);
    currentMode = gameMode;
    modeCode = GAME_MODE;

    // Background Color is initially Black
    glClearColor( 0.0, 0.0, 0.0, 0.0 );

    // Clear pressed keys
    pressedKeys.clear();

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
    pressedKeys.clear();

    // Mark as not initialized
    isInitialized = false;
}

// ========================== //

void run()
{
    // Check if we already have a BreakAll
    if (!isInitialized) return;
    if (running) return;

    // Main Loop
    running = true;
    while (running)
    {
        // Clear
        glClear(GL_COLOR_BUFFER_BIT);

        // Update and draw mode
        currentMode->update();
        currentMode->draw();

        // Check if we should stop
        running = running && glfwGetWindowParam( GLFW_OPENED );

        // Swap the buffer and sleep, to avoid high FPS and CPU usage
        glfwSwapBuffers();
        glfwSleep(0.02);
    }

}

// ========================== //

void stop()
{
    if (!isInitialized) return;
    if (!running) return;
    running = false;
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

    // Try to find the key in the set of currently pressed keys
    std::set<int>::iterator keyPos = pressedKeys.find(Key);
    
    // Add a new Key if this is the first time it is pressed
    if (keyPos == pressedKeys.end() && Status == GLFW_PRESS)
    {
        pressedKeys.insert(Key);
    }
    // Remove a key that was pressed and dispatch the event
    else if (keyPos != pressedKeys.end() && Status == GLFW_RELEASE)
    {
        pressedKeys.erase(keyPos);
        currentMode->onKeyPressed(Key);
    }
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
    currentMode->onMouseMove(glXpos, glYpos);
}

// ========================== //

}; // namespace BreakAll
