#include <iostream>

#include "paddle.h"

namespace BreakAll{

// ========================== //

Paddle::Paddle(Area levelArea, Area levelInfoArea)
    : levelArea(levelArea)
{
    paddleSize.top = 0.04;
    paddleSize.bottom = -0.04;
    paddleSize.left = -0.5;
    paddleSize.right = 0.5;
    
    position.x = (levelArea.left + levelArea.right)/2;
    position.y = levelArea.bottom + 0.06;
    
    paddleMovementBarSize.top = 0.02;
    paddleMovementBarSize.bottom = -0.02;
    paddleMovementBarSize.left = -0.6;
    paddleMovementBarSize.right = 0.6;
    
    paddleMovementBarPos.x = (levelInfoArea.left + levelInfoArea.right) / 2;
    paddleMovementBarPos.y = levelInfoArea.top - 0.03;
    
    paddleMovementMeter = paddleMovementBarSize;
    paddleMovementMeter.left = paddleMovementBarPos.x;
    paddleMovementMeter.right = paddleMovementBarPos.x;
    
    paddleSpeed = 0;
}

// ========================== //

Paddle::~Paddle()
{

}

// ========================== //

void Paddle::step()
{
    if (position.x + paddleSpeed > levelArea.left && position.x + paddleSpeed < levelArea.right)
    {
        position.x += paddleSpeed;   
    }
}

// ========================== //

void Paddle::draw()
{
    //draws Paddle
    glBegin(GL_QUADS);
        glColor3f(1, 1, 1);
        glVertex2f(paddleSize.left + position.x, paddleSize.top + position.y);
        glVertex2f(paddleSize.right + position.x, paddleSize.top + position.y);
        glVertex2f(paddleSize.right + position.x, paddleSize.bottom + position.y);
        glVertex2f(paddleSize.left + position.x, paddleSize.bottom + position.y);
    glEnd();
    
    //draws Bar of movement information
    glBegin(GL_QUADS);
        glColor3f(0.5, 0.5, 0.5);
        glVertex2f(paddleMovementBarSize.left + paddleMovementBarPos.x, paddleMovementBarSize.top + paddleMovementBarPos.y);
        glVertex2f(paddleMovementBarSize.right + paddleMovementBarPos.x, paddleMovementBarSize.top + paddleMovementBarPos.y);
        glVertex2f(paddleMovementBarSize.right + paddleMovementBarPos.x, paddleMovementBarSize.bottom + paddleMovementBarPos.y);
        glVertex2f(paddleMovementBarSize.left + paddleMovementBarPos.x, paddleMovementBarSize.bottom + paddleMovementBarPos.y);
    glEnd();
    
    //draws the bar that indicates the amount of speed of the paddle
    glBegin(GL_QUADS);
        glColor3f(0.9, 0.9, 0.9);
        glVertex2f(paddleMovementMeter.left + paddleMovementBarPos.x, paddleMovementMeter.top + paddleMovementBarPos.y);
        glVertex2f(paddleMovementMeter.right + paddleMovementBarPos.x, paddleMovementMeter.top + paddleMovementBarPos.y);
        glVertex2f(paddleMovementMeter.right + paddleMovementBarPos.x, paddleMovementMeter.bottom + paddleMovementBarPos.y);
        glVertex2f(paddleMovementMeter.left + paddleMovementBarPos.x, paddleMovementMeter.bottom + paddleMovementBarPos.y);
    glEnd();
}

// ========================== //

void Paddle::onKeyPressed(int key)
{   
    if (key == 'J')
    {
        position.x -= 0.1;
    }
    else if (key == 'L')
    {
        position.x += 0.1;
    }
}

// ========================== //

void Paddle::onMouseMove(float x, float y)
{
    if (x < paddleMovementBarPos.x)
    {
        if (x > paddleMovementBarSize.left)
        {
            paddleMovementMeter.left = x;
        }
        else
        {
            paddleMovementMeter.left = paddleMovementBarSize.left;
        }
        
        paddleMovementMeter.right = paddleMovementBarPos.x;
    }
    else if (x > paddleMovementBarPos.x)
    {
        if (x < paddleMovementBarSize.right)
        {
            paddleMovementMeter.right = x;
        }
        else
        {
            paddleMovementMeter.right = paddleMovementBarSize.right;
        }
        
        paddleMovementMeter.left = paddleMovementBarPos.x;
    }
    else
    {
        paddleMovementMeter.left = paddleMovementMeter.right = paddleMovementBarPos.x;
    }
    
    paddleSpeed = 0.2 * (paddleMovementMeter.left - paddleMovementBarPos.x + paddleMovementMeter.right - paddleMovementBarPos.x);
}

// ========================== //

Area Paddle::getPaddleArea()
{
    Area paddleArea = 
    {
        position.y + paddleSize.top,
        position.x + paddleSize.right,
        position.y + paddleSize.bottom,
        position.x + paddleSize.left
    };
    return paddleArea;
}

// ========================== //

void Paddle::reset()
{
    position.x = (levelArea.left + levelArea.right)/2;
    position.y = levelArea.bottom + 0.06;
    paddleSpeed = 0;
    paddleMovementMeter.left = paddleMovementMeter.right = paddleMovementBarPos.x;
}

// ========================== //

void Paddle::print()
{
    std::cout << ">>> Position: (" 
        << position.x << ", " << position.y << ")" << std::endl;
    std::cout << ">>> Velocity: " << this->paddleSpeed << std::endl;
    std::cout << "----------------------" << std::endl;
}

// ========================== //

}; // namespace BreakAll
