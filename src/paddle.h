#ifndef PADDLE_H_INCLUDED
#define PADDLE_H_INCLUDED

#include "Drawable.h"

namespace BreakAll {

// ========================== //

class Paddle: public Drawable
{
    public:
        Paddle(Area levelArea, Area levelInfoArea);
        ~Paddle();
        void step();
        void draw();
        Area getPaddleArea();
        void print();
        void reset();
        virtual void onKeyPressed(int key);
        virtual void onMouseMove(float x, float y);
    private:
        Area levelArea;
        
        Area paddleSize;
        Position position;
        
        Area paddleMovementBarSize;
        Position paddleMovementBarPos;
        
        Area paddleMovementMeter;
        
        float paddleSpeed;
};

// ========================== //

}; // namespace BreakAll

#endif /* PADDLE_H_INCLUDED */
