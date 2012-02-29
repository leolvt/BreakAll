#include <set>
#include <string>

#include "BreakAll.h"
#include "Engine.h"
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
    Drawable* CurrentScreen = 0;
    bool isRunning = false;
    std::set<Engine::Key> pressedKeys;
};

// ============================================== //

/**
 * Handle Key Events.
 */
void OnKeyPressed( Engine::Key k, Engine::KeyState s )
{
    // Mark the key down if it is pressed
    if (s == Engine::KEY_PRESSED) 
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
    Engine::PollEvents();
    if ( !Engine::IsWindowOpen() ) isRunning = false;
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
    Engine::SwapBuffers();
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
    Engine::Init();
    Engine::SetKeyCallback( &OnKeyPressed );

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
    Engine::OpenWindow(ResWidth, ResHeight, WindowTitle);
    Engine::SetTime(0.0);

    // Starts the Game and keep the loop running
    double nextGameTick = Engine::GetTime();
    int loops;

    isRunning = true;
    while( isRunning ) {

        loops = 0;
        while( Engine::GetTime() > nextGameTick && 
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
    Engine::Terminate();

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

