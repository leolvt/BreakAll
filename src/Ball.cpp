#include "Ball.h"
#include <glm/glm.hpp>

namespace BreakAll {

// ========================== //

Ball::Ball(float x, float y, float radius, Area levelArea)
    : X(x), Y(y), radius(radius), levelArea(levelArea)
{
    velX = 0.01;
    velY = 0.02;
}

// ========================== //

void Ball::update()
{
    // Increase Position
    X += velX;
    Y += velY;

    // Check Bounds
    if (X >= levelArea.right || X <= levelArea.left )
    {
        if (X > levelArea.right) X = levelArea.right;
        else if (X < levelArea.left) X = levelArea.left;
        velX *= -1;
    }

    // Check Upper and Lower bounds
    if (Y >= levelArea.top || Y <= levelArea.bottom )
    {
        if (Y > levelArea.top) Y = levelArea.top;
        else if (Y < levelArea.bottom) Y = levelArea.bottom; //velY = 0, velX = 0;;
        velY *= -1;
    }
}

// ========================== //

void Ball::draw()
{
    // Draw Circle using GL_TRIANGLE_FAN
    const float PI = 3.1415926f;
    const int nVertices = 36;
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.90, 0.30, 0.30);
        glVertex2f(X, Y);
        for (int i = 0; i <= nVertices; i++) {
            float deg = 2*PI / nVertices * i;
            float vX = X + radius * glm::cos(deg);
            float vY = Y + radius * glm::sin(deg);
            glVertex2f(vX, vY);
        }
    glEnd();
}

// ========================== //

void Ball::checkCollisionWithPaddle(Paddle * paddle)
{
    Position ballPosition;
    ballPosition.x = X;
    ballPosition.y = Y;
    
    if (paddle->checkCollision(ballPosition))
    {
        //Inverts the ball's speed on Y if it touches the paddle
        velY *= -1;
    }
}

// ========================== //

void Ball::checkCollisionWithBrick(Brick& brick)
{
    // Get brick area
    Area brickArea = brick.getDelimitedArea();

    // Retrieve old position
    Position old = {X-velX, Y-velY};

    // Check for collision on top or bottom
    if (brickArea.left <= X && X <= brickArea.right)
    {
        // Bottom collision
        if (Y+radius >= brickArea.bottom && 
            old.y + radius < brickArea.bottom)
        {
            velY *= -1;
            Y = brickArea.bottom;
        }
        
        // Top collision
        else if (Y-radius <= brickArea.top && 
            old.y-radius > brickArea.top)
        {
            velY *= -1;
            Y = brickArea.top;
        }
    }
    
    // Check for collision on left or right
    else if (brickArea.top >= Y && Y >= brickArea.bottom)
    {
        // Left collision
        if (X+radius >= brickArea.left && 
            old.x + radius < brickArea.left)
        {
            velX *= -1;
            X = brickArea.left;
        }
        
        // Right collision
        else if (X-radius <= brickArea.right && 
            old.x-radius > brickArea.right)
        {
            velX *= -1;
            X = brickArea.right;
        }
    }

    // TODO: Check Collision with Corners
    // Tip: Use distance from center dist(corner, center) <= R
    else 
    {
        // Check Bottom Left
        float diffX = (brickArea.left - X)*(brickArea.left - X);
        float diffY = (brickArea.bottom - Y)*(brickArea.bottom - Y);
        if (diffX + diffY <= radius*radius) 
        {

        }
    }
}

// ========================== //

}; // namespace BreakAll
