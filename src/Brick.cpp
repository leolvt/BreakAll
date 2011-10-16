#include "Brick.h"

namespace BreakAll {

// ========================== //

Brick::Brick(Position p, float width, float height)
    : pos(p), width(width), height(height)
{
    
}

// ========================== //

Brick::~Brick()
{

}

// ========================== //

void Brick::update()
{

}

// ========================== //

void Brick::draw()
{
    // Draw a rectangular brick
    glBegin(GL_QUADS);
        glColor3f(1, 0.75, 0);
        glVertex2f(pos.x - width/2, pos.y + height/2);
        glVertex2f(pos.x + width/2, pos.y + height/2);
        glVertex2f(pos.x + width/2, pos.y - height/2);
        glVertex2f(pos.x - width/2, pos.y - height/2);
    glEnd();
}

// ========================== //

// ========================== //

// ========================== //

// ========================== //

}; // namespace BreakAll
