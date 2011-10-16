#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include "Brick.h"
#include "Drawable.h"
#include "paddle.h"

class Level;

namespace BreakAll {

// ========================== //

class Ball: public Drawable
{
    public:
        Ball(float x, float y, float radius, Area levelArea);
        void update();
        void draw();
        void onKeyPressed(int key) {};
        void onMouseMove(float x, float y) {};
        void checkCollisionWithPaddle(Paddle * paddle);
        void checkCollisionWithBrick(Brick& brick);
        void checkCollisionWithArea(Area area);

    private:
        Area levelArea;
        float X, Y;
        float radius;
        float velX, velY;
};

// ========================== //

}; 

#endif  /* BALL_H_INCLUDED */

