#include "Ball.h"
#include <iostream>
#include <glm/glm.hpp>

namespace BreakAll {

// ========================== //

Ball::Ball(Position p, float radius, glm::vec2 vel, Area levelArea)
    : pos(p), radius(radius), vel(vel), levelArea(levelArea)
{
    valid = true;
}

// ========================== //

void Ball::step()
{
    // Increase Position
    pos.x += vel.x;
    pos.y += vel.y;

    // Check Bounds
    if (pos.x >= levelArea.right || pos.x <= levelArea.left )
    {
        if (pos.x > levelArea.right) pos.x = levelArea.right;
        else if (pos.x < levelArea.left) pos.x = levelArea.left;
        vel.x *= -1;
    }

    // Check Upper and Lower bounds
    if (pos.y >= levelArea.top || pos.y <= levelArea.bottom )
    {
        if (pos.y > levelArea.top) pos.y = levelArea.top;
        else if (pos.y <= levelArea.bottom) 
        {
            vel.x = 0; vel.y = 0;
            valid = false;
        }
        vel.y *= -1;
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
        glVertex2f(pos.x, pos.y);
        for (int i = 0; i <= nVertices; i++) {
            float deg = 2*PI / nVertices * i;
            float vX = pos.x + radius * glm::cos(deg);
            float vY = pos.y + radius * glm::sin(deg);
            glVertex2f(vX, vY);
        }
    glEnd();
}

// ========================== //

bool Ball::collidesWithArea(Area area)
{
    // Retrieve old position
    Position old = {pos.x-vel.x, pos.y-vel.y};

    // We wiil store the normal here
    glm::vec2 normal;

    // Store if we collided or not
    bool collided = false;

    // Check for collision on top or bottom
    if (area.left <= pos.x && pos.x <= area.right)
    {
        // Bottom collision
        if (pos.y+radius >= area.bottom && 
            old.y + radius < area.bottom)
        {
            normal = glm::normalize( glm::vec2(0,-1) );
            pos.y = area.bottom - radius;
            collided = true;
        }
        
        // Top collision
        else if (pos.y-radius <= area.top && 
            old.y-radius > area.top)
        {
            normal = glm::normalize( glm::vec2(0,1) );
            pos.y = area.top + radius;
            collided = true;
        }
    }
    
    // Check for collision on left or right
    else if (area.top >= pos.y && pos.y >= area.bottom)
    {
        // Left collision
        if (pos.x+radius >= area.left && 
            old.x + radius < area.left)
        {
            normal = glm::normalize( glm::vec2(-1,0) );
            pos.x = area.left - radius;
            collided = true;
        }
        
        // Right collision
        else if (pos.x-radius <= area.right && 
            old.x-radius > area.right)
        {
            normal = glm::normalize( glm::vec2(1,0) );
            pos.x = area.right + radius;
            collided = true;
        }
    }

    // Corner Collision
    else 
    {
        // Compute position correction factor
        float corr = glm::sqrt(2.0)/2*radius;

        // Compute corner distances
        float distBL = (area.left - pos.x)*(area.left - pos.x) + 
                       (area.bottom - pos.y)*(area.bottom - pos.y);
        float distBR = (area.right - pos.x)*(area.right - pos.x) +
                       (area.bottom - pos.y)*(area.bottom - pos.y);
        float distTR = (area.right - pos.x)*(area.right - pos.x) +
                       (area.top - pos.y)*(area.top - pos.y);
        float distTL = (area.left - pos.x)*(area.left - pos.x) + 
                       (area.top - pos.y)*(area.top - pos.y);

        // Check corner collision - Bottom Left
        if (distBL <= radius*radius) 
        {
            pos.x = area.left-corr;
            pos.y = area.bottom-corr;
            normal = glm::normalize(glm::vec2(-1,-1));
            collided = true;
        }
        // Check corner collision - Bottom Right
        else if (distBR <= radius*radius) 
        {
            pos.x = area.right + corr;
            pos.y = area.bottom - corr;
            normal = glm::normalize(glm::vec2(1,-1));
            collided = true;
        }
        // Check corner collision - Top Left
        else if (distTL <= radius*radius) 
        {
            pos.x = area.left - corr;
            pos.y = area.top + corr;
            normal = glm::normalize(glm::vec2(-1,1));
            collided = true;
        }
        // Check corner collision - Top Right
        else if (distTR <= radius*radius) 
        {
            pos.x = area.right + corr;
            pos.y = area.top + corr;
            normal = glm::normalize(glm::vec2(1,1));
            collided = true;
        }
    }

    // Reflect the velocity in the case of a collision
    if (collided)
    {
        glm::vec2 velIn = glm::vec2(vel.x, vel.y);
        glm::vec2 velOut = glm::reflect( velIn, normal);
        vel.x = velOut.x;
        vel.y = velOut.y;
    }

    return collided;
}

// ========================== //

void Ball::updateSpeedFromPaddle(float paddleSpeed, Area paddleArea)
{
	//The call to this function is made with the assumption of a collision
	float r = (paddleArea.right - paddleArea.left)*2;
	float middlePaddle = (paddleArea.left + paddleArea.right) / 2;
	float halfPaddle = middlePaddle - paddleArea.left;	
	float angle = 0;
	if (pos.x > middlePaddle)
	{
		angle = 90 - (pos.x - middlePaddle) / halfPaddle * 90;
	}
	else
	{
		angle = (middlePaddle - pos.x) / halfPaddle * 90 + 90;
	}
	if (angle < 0 || angle > 180)
	{
		return;
	}
	const float PI = 3.1415926f;
	float cos = glm::cos(angle / 180 * PI);
	float sin = glm::sin(angle / 180 * PI);
	
	float oldVelMagnitude = glm::sqrt(vel.x*vel.x + vel.y*vel.y);
	vel.x = vel.x*sin + vel.y*cos;
	vel.y = vel.x*cos + vel.y*sin;
	float newVelMagnitude = glm::sqrt(vel.x*vel.x + vel.y*vel.y);
	vel.x *= oldVelMagnitude / newVelMagnitude;
	vel.y *= oldVelMagnitude / newVelMagnitude;
}

// ========================== //

bool Ball::isValid()
{
    return valid;
}

// ========================== //

void Ball::print()
{
    std::cout << ">>> Radius: " << this->radius << std::endl;
    std::cout << ">>> Position: ("<< pos.x <<", "<< pos.y <<")" << std::endl;
    std::cout << ">>> Speed: (" << vel.x << ", " << vel.y << ")" << std::endl;
    std::cout << "----------------------" << std::endl;
}

// ========================== //

}; // namespace BreakAll
