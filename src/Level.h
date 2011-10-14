#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include "Drawable.h"

namespace BreakAll {

// ========================== //

class Level: public Drawable
{
    public:
        Level(Area levelArea, Area levelInfoArea);
        ~Level();
        void update();
        void draw();
        virtual void onKeyPressed(int key);
        virtual void onMouseMove(float x, float y);
    private:
        Area levelArea;
        Area levelInfoArea;
};

// ========================== //

}; // namespace BreakAll

#endif /* LEVEL_H_INCLUDED */
