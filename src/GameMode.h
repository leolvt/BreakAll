#ifndef GAME_MODE_H_INCLUDED
#define GAME_MODE_H_INCLUDED

#include "Level.h"

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
        Level* level;
        OGLFT::Monochrome* mono13;
        OGLFT::Monochrome* mono26;
        bool gameOver;
        int numLives;
        int numPoints;
        int currLevel;
};

// ========================== //

}; // namespace BreakAll

#endif  /* GAME_MODE_H_INCLUDED */

