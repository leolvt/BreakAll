#include "Ball.h"
#include <glm/glm.hpp>

namespace BreakAll {

// ========================== //

Ball::Ball(float x, float y, float radius, Area levelArea)
    : X(x), Y(y), radius(radius), levelArea(levelArea)
{
    velX = 0.02;
    velY = 0.04;
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
        else if (Y < levelArea.bottom) velY = 0, velX = 0;;
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

    // Check for collision
    if (X <= brickArea.right && X >= brickArea.left &&
        Y <= brickArea.top && Y >= brickArea.bottom)
    {
        velX = 0, velY = 0;
    }
}

// ========================== //

}; // namespace BreakAll
