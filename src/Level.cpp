#include "Level.h"

namespace BreakAll {

// ========================== //

Level::Level(Area levelArea, Area levelInfoArea)
    : levelArea(levelArea), levelInfoArea(levelInfoArea)
{

}

// ========================== //

Level::~Level()
{

}

// ========================== //

void Level::update()
{

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

}

// ========================== //

void Level::onKeyPressed(int key)
{

}

// ========================== //

void Level::onMouseMove(float x, float y)
{

}

// ========================== //

}; // namespace BreakAll
