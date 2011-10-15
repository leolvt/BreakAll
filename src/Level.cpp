#include "Level.h"
#include "Ball.h"

namespace BreakAll {

// ========================== //

Level::Level(Area totalArea)
{
    // Calculate the height of the InfoBar
    float infoHeight = (totalArea.top - totalArea.bottom) * 0.1;

    // Assign level area, without the info bar
    this->levelArea = totalArea;
    this->levelArea.bottom += infoHeight;

    // Assign Info Bar area
    levelInfoArea = totalArea;
    levelInfoArea.top = totalArea.bottom + infoHeight;

    Area paddleSize;
    paddleSize.top = 0.05;
    paddleSize.bottom = -0.05;
    paddleSize.left = -0.5;
    paddleSize.right = 0.5;
    
    Position startPosPaddle;
    startPosPaddle.x = (levelArea.left + levelArea.right)/2;
    startPosPaddle.y = levelArea.bottom + 0.06;
    
    paddle = new Paddle(paddleSize, levelArea, startPosPaddle);
    
    // Create the ball
    this->ball = new Ball(0,0, 0.05, this->levelArea);

    // Start the game paused
    paused = true;
}

// ========================== //

Level::~Level()
{
    if (ball != 0)
    {
        delete ball;
        ball = 0;
    }   
}

// ========================== //

void Level::update()
{
    if (paused) return;

    paddle->update();
    ball->update();
}

// ========================== //

void Level::draw()
{
    // Draw the ball
    ball->draw();

    // Draw Level Info Bar
    glBegin(GL_QUADS);
        glColor3f(0.5, 0.5, 0.9);
        glVertex2f(levelInfoArea.left, levelInfoArea.top);
        glVertex2f(levelInfoArea.right, levelInfoArea.top);
        glVertex2f(levelInfoArea.right, levelInfoArea.bottom);
        glVertex2f(levelInfoArea.left, levelInfoArea.bottom);
    glEnd();
    
    paddle->draw();


    // If paused, show a message on the screen
    if (paused)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBegin(GL_QUADS);
           glColor4f(0.5, 0.5, 0.5, 0.5); 
           glVertex2f(levelArea.left, levelArea.top);
           glVertex2f(levelArea.right, levelArea.top);
           glVertex2f(levelArea.right, levelArea.bottom);
           glVertex2f(levelArea.left, levelArea.bottom);
        glEnd();
        glDisable(GL_BLEND);

        OGLFT::Monochrome* f = new OGLFT::Monochrome(
            "DejaVuSansMono.ttf",
            26
        );
        f->setHorizontalJustification(OGLFT::Face::CENTER);
        f->draw(0,0, "PAUSED");
    }
}

// ========================== //

void Level::onKeyPressed(int key)
{
    if (key == 'P')
    {
        paused = !paused;
    }

    paddle->onKeyPressed(key);
}

// ========================== //

void Level::onMouseMove(float x, float y)
{
    paddle->onMouseMove(x, y);
}

// ========================== //

Area Level::getLevelArea()
{
    return this->levelArea;
}

// ========================== //

}; // namespace BreakAll
