#ifndef BREAKALL_H_INCLUDED
#define BREAKALL_H_INCLUDED

#include "Mode.h"

// ========================== //

namespace BreakAll
{
    enum Modes 
    {
        MENU_MODE = 1,
        GAME_MODE = 2
    };

    void initialize(int windowWidth = 800, int windowHeight = 600);
    void run();
    void changeMode(int NewMode);
    void keyCallback(int Key, int Status);
    void mouseCallback(int x, int y);
    void terminate();
};

// ========================== //

#endif  /* BREAKALL_H_INCLUDED */

