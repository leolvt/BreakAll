#ifndef GAME_MODE_H_INCLUDED
#define GAME_MODE_H_INCLUDED

#define OGLFT_NO_SOLID 1
#define OGLFT_NO_QT 1
#include <oglft/OGLFT.h>

#include "Mode.h"

// ========================== //

class GameMode: public Mode
{
    public:
        GameMode();
        ~GameMode();
        void update();
        void draw();
        void onKeyChange(int key, int status);
        void onMouseChange(float x, float y);
    
    private:
        OGLFT::Monochrome *face;
};

// ========================== //

#endif  /* GAME_MODE_H_INCLUDED */

