#include <iostream>

#include "Level.h"
#include "BreakAll.h"
#include "GameMode.h"

namespace BreakAll {

// ========================== //

GameMode::GameMode(Area gameArea)
    : gameArea(gameArea)
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

    // Compute Infobars height
    float totalHeight = gameArea.top - gameArea.bottom; 
    float infoHeight = totalHeight * 0.1;

    // Set Info Bar Area
    this->infoArea = 
    { 
        gameArea.top, 
        gameArea.right, 
        gameArea.top - infoHeight,
        gameArea.left
    };

    // Set Level Area
    this->levelArea = 
    {
        gameArea.top - infoHeight,
        gameArea.right, 
        gameArea.bottom + infoHeight,
        gameArea.left
    };

    // Calculate LevelInfoBar Area
    Area levelInfoArea = 
    {
        gameArea.bottom + infoHeight,
        gameArea.right, 
        gameArea.bottom,
        gameArea.left
    };

    // Create the level
    this->level = new Level(levelArea, levelInfoArea);
}

// ========================== //

GameMode::~GameMode()
{
    if (face != 0) delete face;
    if (level != 0) delete level;
}

// ========================== //

void GameMode::update()
{
    level->update();
}

// ========================== //

void GameMode::draw()
{
    // Draw the Level
    level->draw();

    // Draw the top bar
    glBegin(GL_QUADS);
        glColor3f(0.9, 0.9, 0.9);
        glVertex2f(infoArea.left, infoArea.top);
        glVertex2f(infoArea.right, infoArea.top);
        glVertex2f(infoArea.right, infoArea.bottom);
        glVertex2f(infoArea.left, infoArea.bottom);
    glEnd();

    // Set some Needed properties for the font to work properly
    face->setForegroundColor(0,0,0);
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

    // Measure and draw the font
    //OGLFT::BBox bb = face->measure("Teste de Fonte");
    //std::cout << (bb.y_max_ - bb.y_min_) << std::endl;
    face->draw(infoArea.left + 0.05, infoArea.top - 0.075, "Teste de Fonte");

}

// ========================== //

void GameMode::onKeyPressed(int key)
{
    if (key == 'Q') BreakAll::stop();
    level->onKeyPressed(key);
}

// ========================== //

void GameMode::onMouseMove(float x, float y)
{
//    std::cout << "Mouse at: (" << x << ", " << y << ")" << std::endl;
    level->onMouseMove(x, y);
}

// ========================== //

}; // namespace BreakAll
