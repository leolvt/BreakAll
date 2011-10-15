#ifndef PADDLE_H_INCLUDED
#define PADDLE_H_INCLUDED

#include "Drawable.h"

namespace BreakAll {

// ========================== //

class Paddle: public Drawable
{
    public:
        Paddle(Area paddleSize, Area levelArea, Position startPos);
        ~Paddle();
        void update();
        void draw();
        virtual void onKeyPressed(int key);
        virtual void onMouseMove(float x, float y);
    private:
        Area paddleSize;
        Area levelArea;
        Position position;
};

// ========================== //

}; // namespace BreakAll

#endif /* PADDLE_H_INCLUDED */
