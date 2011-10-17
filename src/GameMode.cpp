#include <iostream>
#include <sstream>

#include "BreakAll.h"
#include "GameMode.h"
#include "Level.h"
#include "Util.h"

#define MIN_ROWS 2
#define MAX_ROWS 1000 // 10

#define MIN_COLS 4
#define MAX_COLS 1000 // 20

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
    this->currNumRows = MIN_ROWS-1;
    this->currNumCols = MIN_COLS-1;
    this->gameOver = false;
    this->paused = true;
    this->currLevel = 0;
    this->level = 0;
    nextLevel();
}

// ========================== //

GameMode::~GameMode()
{
    if (mono13 != 0) delete mono13;
    if (mono26 != 0) delete mono26;
    if (level != 0) delete level;
}

// ========================== //

void GameMode::reset()
{
    // We start with 3 lives
    this->numLives = 3;
    this->numPoints = 0;

    // Start at level 1
    this->gameOver = false;
    this->paused = true;
    this->currLevel = 0;
    prevLevel();
}

// ========================== //

void GameMode::update()
{
    if (!gameOver && !paused) step();
}

// ========================== //

void GameMode::step()
{
    // Step the level level
    level->step();

    // If we have failed, check if we have another life
    if (!level->isAlive())
    {
        // We have more lives
        if (numLives > 1) 
        {
            this->numLives--;
            level->resetBalls();
            level->resetPaddle();
            level->live();
            paused = true;
        }
        else
        {
            numLives = 0;
            this->gameOver = true;
            this->numPoints += level->getPoints();
            if (numPoints < 0) numPoints = 0;
        }
    }
    else if (level->isCleared())
    {
        this->numPoints += level->getPoints();
        if (numPoints < 0) numPoints = 0;
        nextLevel();
    }
}

// ========================== //

void GameMode::nextLevel()
{
    // Clear current level
    if (level != 0) delete level;

    // Build new level
    if (currNumRows < MAX_ROWS) currNumRows++;
    if (currNumCols < MAX_COLS) currNumCols++;
    currLevel++;
    float currPaddleFactor = 0.1;
    if (currLevel < 20) currPaddleFactor = 1.0 - (currLevel-1)*0.0474;
    level = new Level(levelArea, currNumRows, currNumCols, 1+(currLevel/8), currPaddleFactor);
    paused = true;
}

// ========================== //

void GameMode::prevLevel()
{
    // Clear current level
    if (level != 0) delete level;

    // Sanity Check
    if (currLevel <= 1) 
    {
        currLevel = 1;
        currNumRows = MIN_ROWS;
        currNumCols = MIN_COLS;
    }
    else
    {
    // Build new level
        currLevel--;
        if (currNumRows > MIN_ROWS) currNumRows--;
        if (currNumCols > MIN_COLS) currNumCols--;
    }

    float currPaddleFactor = 0.1;
    if (currLevel < 20) currPaddleFactor = 1.0 - (currLevel-1)*0.0474;
    level = new Level(levelArea, currNumRows, currNumCols, 1+(currLevel/5), currPaddleFactor);
    paused = true;
}

// ========================== //

void GameMode::drawTopBar()
{
    // Draw the top bar background
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
    mono26->setVerticalJustification(OGLFT::Face::BASELINE);
}

// ========================== //

void GameMode::draw()
{
    // Draw the Level
    level->draw();

    // Draw the top Bar
    drawTopBar();

    // Handle GameOver drawing
    if (gameOver)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBegin(GL_QUADS);
           glColor4f(0.5, 0.5, 0.5, 0.5); 
           glVertex2f(levelArea.left, levelArea.top);
           glVertex2f(levelArea.right, levelArea.top);
           glVertex2f(levelArea.right, levelArea.bottom);
           glVertex2f(levelArea.left, levelArea.bottom);
        glEnd();
        glDisable(GL_BLEND);

        glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
        mono26->setForegroundColor(0,0,0);
        mono26->setHorizontalJustification(OGLFT::Face::CENTER);
        mono26->draw(0,0, "GAME OVER!!! :(");
        mono26->setHorizontalJustification(OGLFT::Face::ORIGIN);
    }

    // If paused, show a message on the screen
    else if (paused)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBegin(GL_QUADS);
           glColor4f(0.5, 0.5, 0.5, 0.5); 
           glVertex2f(levelArea.left, levelArea.top);
           glVertex2f(levelArea.right, levelArea.top);
           glVertex2f(levelArea.right, levelArea.bottom);
           glVertex2f(levelArea.left, levelArea.bottom);
        glEnd();
        glDisable(GL_BLEND);

        glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
        mono26->setForegroundColor(0,0,0);
        mono26->setHorizontalJustification(OGLFT::Face::CENTER);
        mono26->draw(0,0, "PAUSED");
        mono26->setHorizontalJustification(OGLFT::Face::ORIGIN);
    }
}

// ========================== //

void GameMode::print()
{
    std::cout << "==================================" << std::endl;
    std::cout << "BreakAll -> Game Mode!" << std::endl;
    std::cout << "----------------------" << std::endl;
    std::cout << "> Current Level: " << this->currLevel << std::endl;
    std::cout << "> Number of Lives: " << this->numLives << std::endl;
    std::cout << "> Number of Points: " << this->numPoints << std::endl;
    std::cout << "----------------------" << std::endl;
    this->level->print();
    std::cout << "==================================" << std::endl;
    std::cout << std::endl;
}

// ========================== //

void GameMode::onKeyPressed(int key)
{
    // 'Q' or ESC for Quit
    if (key == 'Q' || key == GLFW_KEY_ESC) BreakAll::stop();

    // 'R' for reset
    if (key == 'R') reset();

    // Next e Previous Levels
    if (key == 'N') nextLevel();
    if (key == 'P') prevLevel();

    // Give and Take Lives
    if (key == GLFW_KEY_KP_ADD) numLives++;
    if (key == GLFW_KEY_KP_SUBTRACT && numLives > 1) numLives--;
    
    // If not paused nor gameover, propagate.
    if (!paused && !gameOver) level->onKeyPressed(key);
}

// ========================== //

void GameMode::onMouseMove(float x, float y)
{
//    std::cout << "Mouse at: (" << x << ", " << y << ")" << std::endl;
    if (!paused && !gameOver) level->onMouseMove(x, y);
}

// ========================== //

void GameMode::onMouseButton(int button)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        paused = !paused;
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        paused = true;
        step();
        print();
    }
}

// ========================== //

}; // namespace BreakAll
