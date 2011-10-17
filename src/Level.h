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
        Level(Area totalArea, int numRows, int numCols, int numBalls, float paddleSizeFactor);
        ~Level();
        void draw();
        void step();
        Area getLevelArea();
        void resetBalls();
        void resetPaddle();
        bool isAlive();
        bool isCleared();
        void live();
        void print();
        int getPoints();
        void onKeyPressed(int key);
        void onMouseMove(float x, float y);
    private:
        Area levelArea;
        Area levelInfoArea;
		bool alive;
		bool cleared;
        int numBalls;
        int points;
        float paddleSizeFactor;
        Paddle * paddle;
        Ball* ball;
        std::list<Brick> bricks;
        std::list<Ball> balls;
};

// ========================== //

}; // namespace BreakAll

#endif /* LEVEL_H_INCLUDED */
