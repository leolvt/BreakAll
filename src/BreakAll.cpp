#define OGLFT_NO_SOLID 1
#define OGLFT_NO_QT 1

#include <GL/glew.h>
#include <GL/glfw.h>
#include <oglft/OGLFT.h>

#include <iostream>

#include "BreakAll.h"

// ========================== //

BreakAll::BreakAll()
{
    this->currentMode = 0;
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

    // Load Font
    OGLFT::Monochrome* face = new OGLFT::Monochrome(
            "/usr/share/fonts/truetype/ttf-dejavu/DejaVuSans.ttf",
            13
    );
    // Always check to make sure the face was properly constructed
    if ( face == 0 || !face->isValid() ) {
        std::cerr << "Could not construct face."  << std::endl;
        return;
    }

    // Set some Needed properties for the font to work properly
    face->setForegroundColor(0,0,0);
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

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

        // Draw "Game Area"
        glBegin(GL_QUADS);
            glColor3f(1.0,1.0,1.0);
            glVertex2f(-1.333, -0.9);
            glVertex2f(-1.333, 0.9);
            glVertex2f(1.333, 0.9);
            glVertex2f(1.333, -0.9);
        glEnd();

        // Draw red quad
        glBegin(GL_QUADS);
            glColor3f(1.0,0.0,0.0);
            glVertex2f(-0.50, -0.50);
            glVertex2f(-0.50, 0.50);
            glVertex2f(0.50, 0.50);
            glVertex2f(0.50, -0.50);
        glEnd();
      
        // Measure and draw the font
        OGLFT::BBox bb = face->measure("Teste de Fonte");
        std::cout << (bb.y_max_ - bb.y_min_) << std::endl;
        face->draw(-1.2333,-0.97333, "Teste de Fonte");

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

