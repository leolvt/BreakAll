#include <SFML/OpenGL.hpp>

#include "GameScreen.h"

namespace BreakAll {

// TODO: Add comments to the functions
// ============================================== //

GameScreen::GameScreen() {
    degree_ = 0.0;
}

// ============================================== //

GameScreen::~GameScreen() {

}

// ============================================== //
 
void GameScreen::step() {
    int t = 5;
    degree_ += (1.0/50.0) * 360/t;
    while (degree_ > 360) degree_ -= 360;
}

// ============================================== //

// TODO: Change the logic to make it independant on the window size
// (i. e.: retrieve the actual window size from BreakAll functions
// and keep all the sizes in member variables, updating when a resize 
// occurs)
void GameScreen::draw() {
    // Pre-compute some sizes
    int wWidth = 800;
    int wHeight = 600;

    int bottomPannelWidth = wWidth;
    int bottomPannelHeight = 20;

    int topPannelWidth = wWidth;
    int topPannelHeight = 40;

    int gameWidth = wWidth;
    int gameHeight = wHeight - bottomPannelHeight - topPannelHeight;

    // Draw the Top Pannel
    float topWidth = ((float)topPannelWidth) / topPannelHeight;
    glViewport(0, wHeight - topPannelHeight, topPannelWidth, topPannelHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-topWidth, topWidth, -1, 1); 
    glMatrixMode(GL_MODELVIEW);

    glBegin(GL_QUADS);
        glColor3f(0.8, 0.2, 0.2);
        glVertex2f(-topWidth, -1);
        glVertex2f( topWidth, -1);
        glVertex2f( topWidth,  1);
        glVertex2f(-topWidth,  1);
    glEnd();

    // Draw the Game
    float gameWidthf = ((float)gameWidth) / gameHeight;
    glViewport(0, bottomPannelHeight, gameWidth, gameHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-gameWidthf, gameWidthf, -1, 1); 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(degree_, 0, 0, -1);

    glBegin(GL_QUADS);
        glColor3f(0.2, 0.2, 0.8);
        glVertex2f(-0.5, -0.5);
        glColor3f(0.2, 0.8, 0.2);
        glVertex2f( 0.5, -0.5);
        glColor3f(0.8, 0.2, 0.2);
        glVertex2f( 0.5,  0.5);
        glColor3f(0.8, 0.8, 0.8);
        glVertex2f(-0.5,  0.5);
    glEnd();
    glLoadIdentity();

    // Draw the Bottom Pannel
    float bottomWidth = ((float)bottomPannelWidth) / bottomPannelHeight;
    glViewport(0, 0, bottomPannelWidth, bottomPannelHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-bottomWidth, bottomWidth, -1, 1); 
    glMatrixMode(GL_MODELVIEW);
    glBegin(GL_QUADS);
        glColor3f(0.2, 0.8, 0.2);
        glVertex2f(-bottomWidth, -1);
        glVertex2f( bottomWidth, -1);
        glVertex2f( bottomWidth,  1);
        glVertex2f(-bottomWidth,  1);
    glEnd();
}

// ============================================== //
    
} /* BreakAll */

