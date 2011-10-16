#include <iostream>

#include "Brick.h"

namespace BreakAll {

// ========================== //

Brick::Brick(Position p, float width, float height)
    : pos(p), width(width), height(height)
{
    this->brickArea.top = p.y + height/2;
    this->brickArea.right = p.x + width/2;
    this->brickArea.bottom = p.y - height/2;
    this->brickArea.left = p.x - width/2;
    this->alive = true;
}

// ========================== //

Brick::~Brick()
{

}

// ========================== //

void Brick::step()
{

}

// ========================== //

void Brick::draw()
{
    if (!alive) return;

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

Area Brick::getDelimitedArea()
{
    return brickArea;
}

// ========================== //

void Brick::die()
{
    this->alive = false;
}

// ========================== //

void Brick::live()
{
    this->alive = true;
}

// ========================== //

bool Brick::isAlive()
{
    return this->alive;
}

// ========================== //

void Brick::print()
{
    std::cout << ">> Is Alive? " << this->alive << std::endl;
    std::cout << ">>> Position: ("<< pos.x <<", "<< pos.y <<")"<< std::endl;
    std::cout << ">>> Size: "<< width <<"x"<< height << std::endl;
    std::cout << "----------------------" << std::endl;
}

// ========================== //

}; // namespace BreakAll
