#include "Ball.h"
#include <glm/glm.hpp>

namespace BreakAll {

// ========================== //

Ball::Ball(float x, float y, float radius)
    : X(x), Y(y), radius(radius)
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
    if (X >= 1.0 || X <= -1.0)
    {
        if (X > 1.0) X = 1.0;
        else if (X < -1.0) X = -1.0;
        velX *= -1;
    }

    if (Y >= 1.0 || Y <= -1.0)
    {
        if (Y > 1.0) Y = 1.0;
        else if ( Y < -1.0) Y = -1.0;
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
        glColor3f(0.50, 0.50, 0.50);
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

// ========================== //

}; // namespace BreakAll
