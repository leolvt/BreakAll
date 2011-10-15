#include "Level.h"

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
}

// ========================== //

Level::~Level()
{

}

// ========================== //

void Level::update()
{
    paddle->update();
}

// ========================== //

void Level::draw()
{
    /*
    // Draw Level Area
    glBegin(GL_QUADS);
        glColor3f(0.0,0.0,0.0);
        glVertex2f(levelArea.left, levelArea.top);
        glVertex2f(levelArea.right, levelArea.top);
        glVertex2f(levelArea.right, levelArea.bottom);
        glVertex2f(levelArea.left, levelArea.bottom);
    glEnd();
    */

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

}; // namespace BreakAll
