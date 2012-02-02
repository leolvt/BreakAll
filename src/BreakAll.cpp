#include "BreakAll.h"

namespace BreakAll {
 
/* Annonymous namespace to hold data */   
namespace {

    // Things used in the game loop
    int TicksPerSecond = 50;
    int SkipTicks = 1000/ TicksPerSecond;
    int MaxFrameSkip = 10;

    // Resolution
    int ResWidth = 800;
    int ResHeight = 600;
};

// ============================================== //

/*
 * Initialize the game, set up the context, read configs and do
 * anything needed before the game starts to run.
 */
void Initialize()
{
    // TODO
    // Load Configs
    // Start the Engine
    // Set up everything
}

// ============================================== //

/*
 * Run the game. The game loop is inside here.
 */
void Run()
{
    // Starts the Game and keep the loop running


    /*
    DWORD next_game_tick = GetTickCount();
    int loops;

    bool game_is_running = true;
    while( game_is_running ) {

        loops = 0;
        while( GetTickCount() > next_game_tick && loops < MaxFrameSkip) {
            update_game();

            next_game_tick += SkipTicks;
            loops++;
        }

        display_game();
    }
    */
}

// ============================================== //

/*
 * After the game has stopped, clean up what is needed and 
 * terminate the game.
 */
void Terminate()
{
    // TODO
    // Terminate the Engine
    // SAve any config needed
    // Closes everything used
}

// ============================================== //

} /* BreakAll */

