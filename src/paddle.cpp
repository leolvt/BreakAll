#include "paddle.h"
#include <GL/glut.h>

namespace BreakAll{

// ========================== //
    
    Paddle::Paddle(Area levelArea)
    {
        paddleSize.top = 0.05;
        paddleSize.bottom = -0.05;
        paddleSize.left = -0.5;
        paddleSize.right = 0.5;
        
        position.x = (levelArea.left + levelArea.right)/2;
        position.y = levelArea.bottom + 0.06;
        
        lastMousePosition = (levelArea.left + levelArea.right)/2;
    }
    
// ========================== //

    Paddle::~Paddle()
    {
    
    }
    
// ========================== //

    void Paddle::update()
    {
        //if ball touches paddle change ball's speed (?)
    }
    
// ========================== //
    
    void Paddle::draw()
    {
        //desenha Paddle
        glBegin(GL_QUADS);
            glColor3f(1, 1, 1);
            glVertex2f(paddleSize.left + position.x, paddleSize.top + position.y);
            glVertex2f(paddleSize.right + position.x, paddleSize.top + position.y);
            glVertex2f(paddleSize.right + position.x, paddleSize.bottom + position.y);
            glVertex2f(paddleSize.left + position.x, paddleSize.bottom + position.y);
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
        
    }
    
// ========================== //

    bool Paddle::checkCollision(Position position)
    {
        //Checks if the position in the argument is inside the paddle
        if (position.x > paddleSize.left + this->position.x && position.x < paddleSize.right + this->position.x &&
            position.y > paddleSize.bottom + this->position.y && position.y < paddleSize.top + this->position.y)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
// ========================== //

}; // namespace BreakAll
