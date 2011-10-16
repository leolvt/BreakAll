#include <iostream>
#include <sstream>

#include "BreakAll.h"
#include "GameMode.h"
#include "Level.h"
#include "Util.h"

namespace BreakAll {

// ========================== //

GameMode::GameMode(Area gameArea)
    : gameArea(gameArea)
{
    // Load Fonts
    mono13 = new OGLFT::Monochrome( "DejaVuSansMono.ttf", 13);
    mono26 = new OGLFT::Monochrome( "DejaVuSansMono.ttf", 26);

    // Always check to make sure the face was properly constructed
    if ( mono26 == 0 || mono13 == 0 || 
         !mono13->isValid() || !mono26->isValid()) 
    {
        std::cerr << "Could not construct face."  << std::endl;
        return;
    }

    // Compute Infobar height
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
        gameArea.bottom,
        gameArea.left
    };

    // We start with 3 lives
    this->numLives = 3;
    this->numPoints = 0;

    // Start at level 1
    this->currLevel = 1;
    this->level = new Level(levelArea);
}

// ========================== //

GameMode::~GameMode()
{
    if (mono13 != 0) delete mono13;
    if (mono26 != 0) delete mono26;
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
        glColor3f(0.5, 0.5, 0.9);
        glVertex2f(infoArea.left, infoArea.top);
        glVertex2f(infoArea.right, infoArea.top);
        glVertex2f(infoArea.right, infoArea.bottom);
        glVertex2f(infoArea.left, infoArea.bottom);
    glEnd();
    
    // Set some Needed properties for the font to work properly
    mono13->setForegroundColor(0,0,0);
    mono26->setForegroundColor(0,0,0);
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

    // Draw the number of lives
    std::string numLivesStr = "Lives: " + intToStr(numLives);
    Position fontPos;
    fontPos.x = infoArea.right - measureTextWidth(mono13, numLivesStr) - 0.05;
    fontPos.y = infoArea.top - measureTextHeight(mono13, numLivesStr) - 0.05;
    mono13->draw(fontPos.x, fontPos.y, numLivesStr.c_str());
    
    // Draw the number of points
    std::string numPointsStr = "Points: " + intToStr(numPoints);
    fontPos.x = infoArea.right - measureTextWidth(mono13, numPointsStr) - 0.05;
    fontPos.y = infoArea.top - 2*measureTextHeight(mono13, numPointsStr) - 0.07;
    mono13->draw(fontPos.x, fontPos.y, numPointsStr.c_str());
    
    // Draw the current level
    std::string levelStr = "Level: " + intToStr(currLevel);
    fontPos.x = infoArea.left + 0.05;
    fontPos.y = (infoArea.top + infoArea.bottom)/2;   
    mono26->setVerticalJustification(OGLFT::Face::MIDDLE);
    mono26->draw(fontPos.x, fontPos.y, levelStr.c_str());
}

// ========================== //

void GameMode::onKeyPressed(int key)
{
    if (key == 'Q' || key == GLFW_KEY_ESC) BreakAll::stop();
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
