#include <iostream>
#include <string>
#include <set>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <SFML/OpenGL.hpp>

#include "BreakAll.h"

namespace BreakAll {

// ============================================== //

/* Annonymous namespace to hold data */
namespace {

    // Things used in the game loop
    int TicksPerSecond = 50;
    sf::Time TickDuration = sf::milliseconds(1.0 / TicksPerSecond);
    int MaxFrameSkip = 10;

    // Window and its properties
    sf::RenderWindow window;
    int ResWidth = 800;
    int ResHeight = 600;
    std::string WindowTitle = "BreakAll 0.2";

    // Game internal clock
    sf::Clock clock;

    // Current Game State
    //Drawable* CurrentScreen = 0;
    bool isRunning = false;
    //std::set<Engine::Key> pressedKeys;
};

// ============================================== //

/**
 * Perform a game step
 */
void Step() {
    //CurrentScreen->Step();
}

// ============================================== //

/**
 * Draw the game
 */
void Draw() {
    //window.clear(sf::Color(150,200,0));
    glClearColor(0.6, 0.8, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //CurrentScreen->Draw();

    window.display();
}

// ============================================== //

/**
 * Handle the events (user inputs, window events, etc)
 */
void HandleEvents() {
    sf::Event event;
    if ( window.pollEvent(event) ) {
        if (event.type == sf::Event::Closed)
        {
            // Stop the main loop
            isRunning = false;
        }
        else if (event.type == sf::Event::Resized)
        {
            // Adjust the viewport when the window is resized
            ResWidth = event.size.width;
            ResHeight = event.size.height;
            glViewport(0, 0, event.size.width, event.size.height);
        }
    }
}

// ============================================== //

/**
 * Initialize the game, set up the context, read configs and do
 * anything needed before the game starts to run.
 */
void Initialize() {
    // TODO: Load Configs
    // TODO: Set up the initial game state

    clock.restart();

    window.create(
        sf::VideoMode(ResWidth, ResHeight),
        WindowTitle,
        sf::Style::Close
    );
}

// ============================================== //

/*
 * Run the game. The game loop is inside here.
 */
void Run() {

    // Define some important control variables
    sf::Time elapsed = sf::milliseconds(0);
    int loops;

    // Restart the clock
    clock.restart();

    // This is the main loop
    isRunning = true;
    while( isRunning ) {

        // Reset the clock, the loop count and
        // sum the elapsed time
        loops = 0;
        elapsed += clock.restart();

        // If enough time has passed we should update the game state, unless
        // we have skipped more frames than the limit, in which case we skip
        // the update and draw
        while( elapsed > TickDuration &&
                loops < MaxFrameSkip)
        {
            // Handle events, update the game count a new possible skip and
            // adjust the time elapsed to try to assure the game update rate
            HandleEvents();
            Step();
            elapsed -= TickDuration;
            loops++;
        }

        Draw();
    }
}

// ============================================== //

/*
 * After the game has stopped, clean up what is needed and
 * terminate the game.
 */
void Terminate() {
    // TODO: Save any config needed
    // TODO: Terminate the frameworks...
    // Close the window
    window.close();
}

// ============================================== //

} /* BreakAll */

