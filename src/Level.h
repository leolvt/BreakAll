#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include "Ball.h"
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
    private:
        Area levelArea;
        Area levelInfoArea;
		bool paused;
        Paddle * paddle;
        Ball* ball;
};

// ========================== //

}; // namespace BreakAll

#endif /* LEVEL_H_INCLUDED */
