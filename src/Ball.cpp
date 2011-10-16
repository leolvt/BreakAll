#include "Ball.h"
#include <iostream>
#include <glm/glm.hpp>

namespace BreakAll {

// ========================== //

Ball::Ball(float x, float y, float radius, Area levelArea)
    : X(x), Y(y), radius(radius), levelArea(levelArea)
{
    velX = 0.01;
    velY = 0.02;
    valid = true;
}

// ========================== //

void Ball::step()
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
        else if (Y <= levelArea.bottom) 
        {
            velX = 0; velY = 0;
            valid = false;
        }
        velY *= -1;
    }
}

// ========================== //

void Ball::draw()
{
    if (!valid) return;

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

bool Ball::collidesWithArea(Area area)
{
    // Retrieve old position
    Position old = {X-velX, Y-velY};

    // We wiil store the normal here
    glm::vec2 normal;

    // Store if we collided or not
    bool collided = false;

    // Check for collision on top or bottom
    if (area.left <= X && X <= area.right)
    {
        // Bottom collision
        if (Y+radius >= area.bottom && 
            old.y + radius < area.bottom)
        {
            normal = glm::normalize( glm::vec2(0,-1) );
            Y = area.bottom - radius;
            collided = true;
        }
        
        // Top collision
        else if (Y-radius <= area.top && 
            old.y-radius > area.top)
        {
            normal = glm::normalize( glm::vec2(0,1) );
            Y = area.top + radius;
            collided = true;
        }
    }
    
    // Check for collision on left or right
    else if (area.top >= Y && Y >= area.bottom)
    {
        // Left collision
        if (X+radius >= area.left && 
            old.x + radius < area.left)
        {
            normal = glm::normalize( glm::vec2(-1,0) );
            X = area.left - radius;
            collided = true;
        }
        
        // Right collision
        else if (X-radius <= area.right && 
            old.x-radius > area.right)
        {
            normal = glm::normalize( glm::vec2(1,0) );
            X = area.right + radius;
            collided = true;
        }
    }

    // Corner Collision
    else 
    {
        // Compute position correction factor
        float corr = glm::sqrt(2.0)/2*radius;

        // Compute corner distances
        float distBL = (area.left - X)*(area.left - X) + 
                       (area.bottom - Y)*(area.bottom - Y);
        float distBR = (area.right - X)*(area.right - X) +
                       (area.bottom - Y)*(area.bottom - Y);
        float distTR = (area.right - X)*(area.right - X) +
                       (area.top - Y)*(area.top - Y);
        float distTL = (area.left - X)*(area.left - X) + 
                       (area.top - Y)*(area.top - Y);

        // Check corner collision - Bottom Left
        if (distBL <= radius*radius) 
        {
            X = area.left-corr;
            Y = area.bottom-corr;
            normal = glm::normalize(glm::vec2(-1,-1));
            collided = true;
        }
        // Check corner collision - Bottom Right
        else if (distBR <= radius*radius) 
        {
            X = area.right + corr;
            Y = area.bottom - corr;
            normal = glm::normalize(glm::vec2(1,-1));
            collided = true;
        }
        // Check corner collision - Top Left
        else if (distTL <= radius*radius) 
        {
            X = area.left - corr;
            Y = area.top + corr;
            normal = glm::normalize(glm::vec2(-1,1));
            collided = true;
        }
        // Check corner collision - Top Right
        else if (distTR <= radius*radius) 
        {
            X = area.right + corr;
            Y = area.top + corr;
            normal = glm::normalize(glm::vec2(1,1));
            collided = true;
        }
    }

    // Reflect the velocity in the case of a collision
    if (collided)
    {
        glm::vec2 velIn = glm::vec2(velX, velY);
        glm::vec2 velOut = glm::reflect( velIn, normal);
        velX = velOut.x;
        velY = velOut.y;
    }

    return collided;
}

// ========================== //

bool Ball::isValid()
{
    return valid;
}

// ========================== //

}; // namespace BreakAll
