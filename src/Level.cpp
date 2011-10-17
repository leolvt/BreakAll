#include "Level.h"

#include <iostream>

namespace BreakAll {


// ========================== //

Level::Level(Area totalArea, int numRows, int numCols, int numBalls, float paddleSizeFactor)
{
    // Calculate the height of the InfoBar
    float infoHeight = (totalArea.top - totalArea.bottom) * 0.1;

    // Assign level area, without the info bar
    this->levelArea = totalArea;
    this->levelArea.bottom += infoHeight;

    // Assign Info Bar area
    levelInfoArea = totalArea;
    levelInfoArea.top = totalArea.bottom + infoHeight;

    // Create paddle
    this->paddleSizeFactor = paddleSizeFactor;
    resetPaddle();

    // Create the balls
    this->numBalls = numBalls;
    resetBalls();

    // Create bricks (6x8)
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
    cleared = false;
}

// ========================== //

Level::~Level()
{
    bricks.clear();
    balls.clear();
}

// ========================== //

void Level::step()
{
    // Update paddle, ball and bricks
    paddle->step();

    // Check for collision between balls and bricks
    bool noMoreBricks = true;
    for (auto b = balls.begin(); b!= balls.end(); b++) {
        b->step();
        for (auto brick = bricks.begin(); brick != bricks.end(); brick++) {
            if ( !brick->isAlive() ) continue;
            if ( b->collidesWithArea(brick->getDelimitedArea()) )
            {
                brick->die();
            }
            noMoreBricks = false;
            bool hitPaddle = b->collidesWithArea(paddle->getPaddleArea());
            if (hitPaddle)
            {
                b->updateSpeedFromPaddle(paddle->getPaddleSpeed());
            }
        }
        if (noMoreBricks) break;
    }

    // Check if we destroyed all bricks
    if (noMoreBricks) 
    {
        this->cleared = true;
    }

    // Check if any of the balls has fallen
    for (auto b = balls.begin(); b != balls.end(); b++) {
        if (!b->isValid()) 
        {
            this->alive = false;
            break;
        }
    }

}

// ========================== //

void Level::draw()
{
    // Draw the brick(s)
    for (auto brick = bricks.begin(); brick != bricks.end(); brick++) {
        brick->draw();
    }

    // Draw the balls
    for (auto b = balls.begin(); b != balls.end(); b++) {
        b->draw();
    }

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

bool Level::isCleared()
{
    return this->cleared;
}

// ========================== //

void Level::onKeyPressed(int key)
{
    // Propagate to paddle
    paddle->onKeyPressed(key);

    // Propagate to brick
    for (auto brick = bricks.begin(); brick != bricks.end(); brick++)
    {
        brick->onKeyPressed(key);
    }

    // Propagate to balls
    for (auto b = balls.begin(); b != balls.end(); b++)
    {
        b->onKeyPressed(key);
    }
}

// ========================== //

void Level::onMouseMove(float x, float y)
{
    // Propagate to Paddle
    paddle->onMouseMove(x, y);

    // Propagate to bricks
    for (auto brick = bricks.begin(); brick != bricks.end(); brick++)
    {
        brick->onMouseMove(x, y);
    }

    // Propagate to balls
    for (auto b = balls.begin(); b != balls.end(); b++)
    {
        b->onMouseMove(x, y);
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
    float velXwidth = 0.04;
    float velXorig = -0.02;
    glm::vec2 vel;
    Position p;
    balls.clear();
    for (int i = 0; i < numBalls; i++) {
        vel.x = velXorig + (velXwidth)/(2*numBalls+1)*(2*i+1);
        vel.y = 0.02 - 0.005*i;
        p.x = 0;
        p.y = levelArea.bottom+0.3;
        Ball B(p, 0.05, vel, this->levelArea);
        balls.push_back(B);
    }
}

// ========================== //

void Level::resetPaddle()
{
    if (paddle != 0) delete paddle;
    paddle = new Paddle(levelArea, levelInfoArea, paddleSizeFactor);
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
    int idx = 1;
    for (auto b = balls.begin(); b != balls.end(); b++)
    {
        std::cout << "Ball #" << idx++ << " Info" << std::endl;
        std::cout << "----------------------" << std::endl;
        b->print();
    }
    idx = 1;
    for (auto brick = bricks.begin(); brick != bricks.end(); brick++)
    {
        std::cout << "Brick #" << idx++ << " Info" << std::endl;
        std::cout << "----------------------" << std::endl;
        brick->print();
    }
}

// ========================== //

}; // namespace BreakAll
