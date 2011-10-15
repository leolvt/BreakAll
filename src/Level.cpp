#include "Level.h"
#include "Ball.h"

namespace BreakAll {

// ========================== //

Level::Level(Area levelArea, Area levelInfoArea)
    : levelArea(levelArea), levelInfoArea(levelInfoArea)
{
    Area paddleSize;
    paddleSize.top = 0.05;
    paddleSize.bottom = -0.05;
    paddleSize.left = -0.5;
    paddleSize.right = 0.5;
    
    Position startPosPaddle;
    startPosPaddle.x = (levelArea.left + levelArea.right)/2;
    startPosPaddle.y = levelArea.bottom + 0.06;
    
    paddle = new Paddle(paddleSize, levelArea, startPosPaddle);
    this->ball = new Ball(0,0, 0.05);
}

// ========================== //

Level::~Level()
{
    if (ball != 0)
    {
        delete ball;
        ball = 0;
    }   
}

// ========================== //

void Level::update()
{
    paddle->update();
    ball->update();
}

// ========================== //

void Level::draw()
{
    ball->draw();

    // Draw Level Info Bar
    glBegin(GL_QUADS);
        glColor3f(0.9, 0.9, 0.9);
        glVertex2f(levelInfoArea.left, levelInfoArea.top);
        glVertex2f(levelInfoArea.right, levelInfoArea.top);
        glVertex2f(levelInfoArea.right, levelInfoArea.bottom);
        glVertex2f(levelInfoArea.left, levelInfoArea.bottom);
    glEnd();
    
    paddle->draw();
}

// ========================== //

void Level::onKeyPressed(int key)
{
    paddle->onKeyPressed(key);
}

// ========================== //

void Level::onMouseMove(float x, float y)
{
    paddle->onMouseMove(x, y);
}

// ========================== //

Area Level::getLevelArea()
{
    return this->levelArea;
}

// ========================== //

}; // namespace BreakAll
