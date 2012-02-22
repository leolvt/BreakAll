#include <set>
#include <string>

#include "BreakAll.h"
#include "Engine.h"
#include "OpenGLEngine.h"
#include "Menu.h"

namespace BreakAll {
 
// ============================================== //

/* Annonymous namespace to hold data */   
namespace {

    // Things used in the game loop
    int TicksPerSecond = 50;
    double SkipTicks = 1.0 / TicksPerSecond;
    int MaxFrameSkip = 10;

    // Window Properties
    int ResWidth = 800;
    int ResHeight = 600;
    std::string WindowTitle = "BreakAll 0.1";

    // Current Game State
    Engine* CurrentEngine = 0;
    Drawable* CurrentScreen = 0;
    bool isRunning = false;
    std::set<Key> pressedKeys;
};

// ============================================== //

/**
 * Handle Key Events.
 */
void OnKeyPressed( Key k, KeyAction a )
{
    // Mark the key down if it is pressed
    if (a == KEY_PRESSED) 
    {
        pressedKeys.insert(k);
    }
    // And remove it otherwise
    else if (pressedKeys.erase(k) != 0)
    {
        // When a key was pressed and released, dispatch 
        // the event to the current screen
        CurrentScreen->OnKeyPressed(k);
    }
}

// ============================================== //

/**
 * Poll Events and Handle those not bound to a callback
 */
void HandleEvents()
{
    CurrentEngine->PollEvents();
    if (! CurrentEngine->IsWindowOpen() ) isRunning = false;
}

// ============================================== //

/**
 * Perform a game step
 */
void Step()
{
    CurrentScreen->Step();
}

// ============================================== //

/**
 * Draw the game 
 */
void Draw()
{
    CurrentScreen->Draw();
    CurrentEngine->SwapBuffers();
}

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
    if (CurrentEngine == 0)
    {
        CurrentEngine = new OpenGLEngine();
    }

    // Set up the menu
    if (CurrentScreen == 0) 
    {
        CurrentScreen = new Menu();
    }
}

// ============================================== //

/*
 * Run the game. The game loop is inside here.
 */
void Run()
{
    // Reset Timer and Open Window
    CurrentEngine->OpenWindow(ResWidth, ResHeight, WindowTitle);
    CurrentEngine->SetTime(0.0);

    // Starts the Game and keep the loop running
    double nextGameTick = CurrentEngine->GetTime();
    int loops;

    isRunning = true;
    while( isRunning ) {

        loops = 0;
        while( CurrentEngine->GetTime() > nextGameTick && 
                loops < MaxFrameSkip) 
        {
            Step();
            nextGameTick += SkipTicks;
            loops++;
        }

        Draw();
        HandleEvents();
    }
}

// ============================================== //

/*
 * After the game has stopped, clean up what is needed and 
 * terminate the game.
 */
void Terminate()
{
    // Terminate the Engine
    if (CurrentEngine != 0) delete CurrentEngine;

    // TODO
    // Save any config needed
    // Closes everything used
}

// ============================================== //

void Stop()
{
    isRunning = false;
}

// ============================================== //

} /* BreakAll */

