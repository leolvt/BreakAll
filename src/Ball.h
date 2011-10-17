#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include <glm/glm.hpp>

#include "Brick.h"
#include "Drawable.h"
#include "paddle.h"

class Level;

namespace BreakAll {

// ========================== //

class Ball: public Drawable
{
    public:
        Ball(Position p, float radius, glm::vec2 vel, Area levelArea);
        void step();
        void draw();
        void print();
        bool collidesWithArea(Area area);
        bool updateSpeedFromPaddle(float paddleSpeed);
        bool isValid();
        void onKeyPressed(int key) {};
        void onMouseMove(float x, float y) {};

    private:
        bool valid;
        Area levelArea;
        Position pos;
        float radius;
        glm::vec2 vel;
};

// ========================== //

}; 

#endif  /* BALL_H_INCLUDED */

