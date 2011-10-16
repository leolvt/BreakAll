#ifndef GAME_MODE_H_INCLUDED
#define GAME_MODE_H_INCLUDED

#include "Level.h"
#include "Mode.h"

namespace BreakAll {

// ========================== //

class GameMode: public Mode
{
    public:
        GameMode(Area gameArea);
        ~GameMode();
        void update();
        void draw();
        void drawTopBar();
        void onKeyPressed(int key);
        void onMouseMove(float x, float y);
        void step();
        void reset();
    
    private:
        Area gameArea;
        Area levelArea;
        Area infoArea;
        Level* level;
        OGLFT::Monochrome* mono13;
        OGLFT::Monochrome* mono26;
        bool gameOver;
        bool paused;
        int numLives;
        int numPoints;
        int currLevel;
};

// ========================== //

}; // namespace BreakAll

#endif  /* GAME_MODE_H_INCLUDED */

