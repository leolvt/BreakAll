#ifndef PADDLE_H_INCLUDED
#define PADDLE_H_INCLUDED

#include "Drawable.h"

namespace BreakAll {

// ========================== //

class Paddle: public Drawable
{
    public:
        Paddle(Area levelArea);
        ~Paddle();
        void update();
        void draw();
        virtual void onKeyPressed(int key);
        virtual void onMouseMove(float x, float y);
    private:
        Area paddleSize;
        Position position;
};

// ========================== //

}; // namespace BreakAll

#endif /* PADDLE_H_INCLUDED */
