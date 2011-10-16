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
        void update();
        void draw();
        void onKeyPressed(int key);
        void onMouseMove(float x, float y);
        Area getLevelArea();
        void resetBalls();
        bool isAlive();
        void live();
    private:
        Area levelArea;
        Area levelInfoArea;
		bool paused;
		bool alive;
        Paddle * paddle;
        Ball* ball;
        std::list<Brick> bricks;
};

// ========================== //

}; // namespace BreakAll

#endif /* LEVEL_H_INCLUDED */
