#include <iostream>

#include "GameMode.h"

// ========================== //

GameMode::GameMode()
{
    // Load Font
    face = new OGLFT::Monochrome(
            "DejaVuSansMono.ttf",
            13
    );
    // Always check to make sure the face was properly constructed
    if ( face == 0 || !face->isValid() ) {
        std::cerr << "Could not construct face."  << std::endl;
        return;
    }
}

// ========================== //

GameMode::~GameMode()
{
    if (face != 0) delete face;
}

// ========================== //

void GameMode::update()
{

}

// ========================== //

void GameMode::draw()
{
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

    // Set some Needed properties for the font to work properly
    face->setForegroundColor(0,0,0);
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

    // Measure and draw the font
    OGLFT::BBox bb = face->measure("Teste de Fonte");
    //std::cout << (bb.y_max_ - bb.y_min_) << std::endl;
    face->draw(-1.2333,-0.97333, "Teste de Fonte");

}

// ========================== //

void GameMode::onKeyChange(int key, int status)
{
    std::cout << "Key " << (char) key << " pressed/released." << std::endl;
}

// ========================== //

void GameMode::onMouseChange(float x, float y)
{
    std::cout << "Mouse at: (" << x << ", " << y << ")" << std::endl;
}

// ========================== //

