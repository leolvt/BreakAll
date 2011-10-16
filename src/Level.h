#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <list>

#include "Ball.h"
#include "Brick.h"
#include "Drawable.h"
#include "paddle.h"

namespace BreakAll {

// ========================== //

class Level: public Drawable
{
    public:
        Level(Area totalArea);
        ~Level();
        void draw();
        void step();
        Area getLevelArea();
        void resetBalls();
        bool isAlive();
        void live();
        void onKeyPressed(int key);
        void onMouseMove(float x, float y);
    private:
        Area levelArea;
        Area levelInfoArea;
		bool alive;
        Paddle * paddle;
        Ball* ball;
        std::list<Brick> bricks;
};

// ========================== //

}; // namespace BreakAll

#endif /* LEVEL_H_INCLUDED */
