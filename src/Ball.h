#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include "Drawable.h"

namespace BreakAll {

// ========================== //

class Ball: public Drawable
{
    public:
        Ball(float x, float y, float radius);
        void update();
        void draw();
        void onKeyPressed(int key) {};
        void onMouseMove(float x, float y) {};

    private:
        float X, Y;
        float radius;
        float velX, velY;
};

// ========================== //

}; 

#endif  /* BALL_H_INCLUDED */

