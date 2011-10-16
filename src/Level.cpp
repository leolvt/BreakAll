#include "Level.h"

#include <iostream>

namespace BreakAll {


// ========================== //

Level::Level(Area totalArea)
{
    // Calculate the height of the InfoBar
    float infoHeight = (totalArea.top - totalArea.bottom) * 0.1;

    // Assign level area, without the info bar
    this->levelArea = totalArea;
    this->levelArea.bottom += infoHeight;

    // Assign Info Bar area
    levelInfoArea = totalArea;
    levelInfoArea.top = totalArea.bottom + infoHeight;

    Area paddleSize;
    paddleSize.top = 0.05;
    paddleSize.bottom = -0.05;
    paddleSize.left = -0.5;
    paddleSize.right = 0.5;
    
    Position startPosPaddle;
    startPosPaddle.x = (levelArea.left + levelArea.right)/2;
    startPosPaddle.y = levelArea.bottom + 0.06;
    
    paddle = new Paddle(levelArea, levelInfoArea);
    
    // Create the ball
    this->ball = new Ball(0,-0.1, 0.05, this->levelArea);

    // Create bricks (6x8)
    int numCols = 8; int numRows = 6;
    float levelHeight = levelArea.top - levelArea.bottom;
    float levelWidth = levelArea.right - levelArea.left;
    float brickWidth = levelWidth*0.9 / numCols;
    float brickHeight = levelHeight*0.45 / numRows;
    Position topLeft = {
        levelArea.left + 0.05f*levelWidth,
        levelArea.top - 0.05f*levelHeight
    }; 

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            Position brickCenter = topLeft;
            brickCenter.x += brickWidth*j + 0.5*brickWidth;
            brickCenter.y -= brickHeight*i + 0.5*brickHeight;
            bricks.push_back(Brick(brickCenter, brickWidth*0.75, brickHeight*0.75));
        }
    }

    // Start the game 
    alive = true;
}

// ========================== //

Level::~Level()
{
    if (ball != 0)
    {
        delete ball;
        ball = 0;
    }   
    bricks.clear();
}

// ========================== //

void Level::step()
{
    // Update paddle, ball and bricks
    paddle->step();
    ball->step();
    bool noMoreBricks = true;
    for (auto brick = bricks.begin(); brick != bricks.end(); brick++) {
        if ( !brick->isAlive() ) continue;
        if ( ball->collidesWithArea(brick->getDelimitedArea()) )
        {
            brick->die();
        }
        noMoreBricks = false;
    }
    ball->collidesWithArea(paddle->getPaddleArea());

    // Check if we destroyed all bricks
    // HANDLE levelCleared
//    if (noMoreBricks) paused = true;

    // Check if the ball has fallen
    if (!ball->isValid()) 
    {
        this->alive = false;
    }

}

// ========================== //

void Level::draw()
{
    // Draw the brick(s)
    for (auto brick = bricks.begin(); brick != bricks.end(); brick++) {
        brick->draw();
    }

    // Draw the ball
    ball->draw();

    // Draw Level Info Bar
    glBegin(GL_QUADS);
        glColor3f(0.5, 0.5, 0.9);
        glVertex2f(levelInfoArea.left, levelInfoArea.top);
        glVertex2f(levelInfoArea.right, levelInfoArea.top);
        glVertex2f(levelInfoArea.right, levelInfoArea.bottom);
        glVertex2f(levelInfoArea.left, levelInfoArea.bottom);
    glEnd();

    // Draw the paddle
    paddle->draw();
}

// ========================== //

void Level::onKeyPressed(int key)
{
    paddle->onKeyPressed(key);
    ball->onKeyPressed(key);
    for (auto brick = bricks.begin(); brick != bricks.end(); brick++)
    {
        brick->onKeyPressed(key);
    }
}

// ========================== //

void Level::onMouseMove(float x, float y)
{
    paddle->onMouseMove(x, y);
    ball->onMouseMove(x, y);
    for (auto brick = bricks.begin(); brick != bricks.end(); brick++)
    {
        brick->onMouseMove(x, y);
    }
}

// ========================== //

Area Level::getLevelArea()
{
    return this->levelArea;
}

// ========================== //

void Level::resetBalls()
{
    delete this->ball;
    this->ball = new Ball(0,-0.1, 0.05, this->levelArea);
}

// ========================== //

void Level::resetPaddle()
{
    paddle->reset();
}

// ========================== //

bool Level::isAlive()
{
    return this->alive;
}

// ========================== //

void Level::live()
{
    this->alive = true;
}

// ========================== //

void Level::print()
{
    // Compute Valid Bricks
    int validBricks  = 0;
    for (auto brick = bricks.begin(); brick != bricks.end(); brick++)
    {
        if (brick->isAlive()) validBricks++;
    }

    std::cout << "Level Info" << std::endl;
    std::cout << "----------------------" << std::endl;
    std::cout << ">> Is Alive? " << this->alive << std::endl;
    std::cout << ">> Num of Bricks: " << this->bricks.size() << std::endl;
    std::cout << ">> Num of Valid Bricks: " << validBricks << std::endl;
    std::cout << "----------------------" << std::endl;
    std::cout << "Paddle Info" << std::endl;
    std::cout << "----------------------" << std::endl;
    this->paddle->print();
    std::cout << "Ball Info" << std::endl;
    std::cout << "----------------------" << std::endl;
    this->ball->print();
    int idx = 1;
    for (auto brick = bricks.begin(); brick != bricks.end(); brick++)
    {
        std::cout << "Brick #" << idx++ << " Info" << std::endl;
        std::cout << "----------------------" << std::endl;
        brick->print();
    }
}

// ========================== //

}; // namespace BreakAll
