#ifndef BRICK_H_INCLUDED
#define BRICK_H_INCLUDED

#include "Drawable.h"

namespace BreakAll {

// ========================== //

class Brick: public Drawable
{
    public:
        Brick(Position p, float width, float length);
        ~Brick();
        void update();
        void draw();
        void onKeyPressed(int key) {};
        void onMouseMove(float x, float y) {};
        Area getDelimitedArea();
        void die();
        void live();
        bool isAlive();
    private:
        Position pos;
        Area brickArea;
        bool alive;
        float width;
        float height;
};

// ========================== //

}; // namespace BreakAll

#endif  /* BRICK_H_INCLUDED */

