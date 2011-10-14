#ifndef GAME_MODE_H_INCLUDED
#define GAME_MODE_H_INCLUDED

#include "Drawable.h"

namespace BreakAll {

// ========================== //

class GameMode: public Drawable
{
    public:
        GameMode(Area gameArea);
        ~GameMode();
        void update();
        void draw();
        void onKeyPressed(int key);
        void onMouseMove(float x, float y);
    
    private:
        Area gameArea;
        Area levelArea;
        Area infoArea;
        OGLFT::Monochrome *face;
        Drawable* level;
};

// ========================== //

}; // namespace BreakAll

#endif  /* GAME_MODE_H_INCLUDED */

