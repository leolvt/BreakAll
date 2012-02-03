#include <string>

#include <GL/glew.h>
#include <GL/glfw.h>

#include "BreakAll.h"
#include "Engine.h"
#include "OpenGLEngine.h"

namespace BreakAll {
 
/* Annonymous namespace to hold data */   
namespace {

    // Things used in the game loop
    int TicksPerSecond = 50;
    double SkipTicks = 1.0 / TicksPerSecond;
    int MaxFrameSkip = 10;

    // Window Properties
    int ResWidth = 800;
    int ResHeight = 600;
    std::string WindowTitle = "BreakAll 0.1";

    // Current Engine
    Engine* CurrentEngine = 0;
};

// ============================================== //

void draw()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5, 5, 5,   0, 0, 0,   0, 1, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 800.0/600.0, 1, 100);
    glMatrixMode(GL_MODELVIEW);

    glBegin(GL_TRIANGLES);
        glColor3f(1, 0.1, 0.1);
        glVertex3d( 0,  1,  0);
        glVertex3d(-1,  0,  1);
        glVertex3d( 1,  0,  1);

        glColor3f(0.1, 1, 0.1);
        glVertex3d( 0,  1,  0);
        glVertex3d( 1,  0,  1);
        glVertex3d( 1,  0, -1);

        glColor3f(0.1, 0.1, 1);
        glVertex3d( 0,  1,  0);
        glVertex3d(-1,  0,  1);
        glVertex3d(-1,  0, -1);

        glColor3f(0.1, 1, 1);
        glVertex3d( 0,  1,  0);
        glVertex3d(-1,  0, -1);
        glVertex3d( 1,  0, -1);

        glColor3f(1, 1, 0.1);
        glVertex3d(-1,  0,  1);
        glVertex3d(-1,  0, -1);
        glVertex3d( 1,  0, -1);
        glVertex3d( 1,  0, -1);
        glVertex3d( 1,  0,  1);
        glVertex3d(-1,  0,  1);
    glEnd();


    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    // left, right, top, bottom
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //gluLookAt(0, 0, 5,   0, 0, 0,   0, 1, 0);

    //glTranslated(1, 1, 0);
    //glScalef(2,2,2);

    glBegin(GL_TRIANGLES);
        glColor3f(1, 0.1, 1);
        glVertex2d(-1,   -1);
        glVertex2d(-1,   -0.8);
        glVertex2d(-0.8, -1);
    glEnd();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    CurrentEngine->SwapBuffers();
}

// ============================================== //

/*
 * Initialize the game, set up the context, read configs and do
 * anything needed before the game starts to run.
 */
void Initialize()
{
    // TODO
    // Load Configs
    
    // Start the Engine
    if (CurrentEngine == 0)
    {
        CurrentEngine = new OpenGLEngine();
    }

    // Set up everything
}

// ============================================== //

/*
 * Run the game. The game loop is inside here.
 */
void Run()
{
    // Reset Timer and Open Window
    CurrentEngine->OpenWindow(ResWidth, ResHeight, WindowTitle);
    CurrentEngine->SetTime(0.0);

    // Starts the Game and keep the loop running
    double nextGameTick = CurrentEngine->GetTime();
    int loops;

    bool isRunning = true;
    while( isRunning ) {

        loops = 0;
        while( CurrentEngine->GetTime() > nextGameTick && 
                loops < MaxFrameSkip) 
        {
            //updateGame();
            nextGameTick += SkipTicks;
            loops++;
        }

        draw();
        isRunning = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
    }
}

// ============================================== //

/*
 * After the game has stopped, clean up what is needed and 
 * terminate the game.
 */
void Terminate()
{
    // Terminate the Engine
    if (CurrentEngine != 0) delete CurrentEngine;

    // TODO
    // Save any config needed
    // Closes everything used
}

// ============================================== //

} /* BreakAll */

