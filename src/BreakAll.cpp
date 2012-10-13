#include <string>
#include <iostream>

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <SFML/OpenGL.hpp>

#include "BreakAll.h"
#include "GameScreen.h"

namespace BreakAll {

// ============================================== //

/* Annonymous namespace to hold data */
namespace {

    // Things used in the game loop
    const int kTicksPerSecond = 50;
    const sf::Time kTickDuration = sf::seconds(1.0 / kTicksPerSecond);
    const int kMaxFrameSkip = 10;

    // Window and its properties
    sf::RenderWindow window;
    int resWidth = 800;
    int resHeight = 600;
    std::string windowTitle = "BreakAll 0.2";

    // Game internal clock
    sf::Clock clock;

    // Current Game State
    GameScreen* currentScreen = 0;
    bool isRunning = false;
};

// ============================================== //

sf::RenderWindow& GetWindow() {
    return window;
}

// ============================================== //

/**
 * Perform a game step
 */
void Step() {
    if (currentScreen) currentScreen->step();
}

// ============================================== //

/**
 * Draw the game
 */
void Draw() {
    // TODO: Check if the code of window.clear always
    // calls glClearColor
    
    //window.clear(sf::Color(150,200,0));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (currentScreen) currentScreen->draw();
    window.display();
}

// ============================================== //

/**
 * Handle the events (user inputs, window events, etc)
 */
void HandleEvents() {
    // Poll and dispatch the events
    sf::Event event;
    while ( window.pollEvent(event) ) {
        if (event.type == sf::Event::Closed)
        {
            // Stop when the window is closed
            isRunning = false;
        }
        else if (event.type == sf::Event::Resized)
        {
            // Adjust the viewport when the window is resized
            resWidth = event.size.width;
            resHeight = event.size.height;
            glViewport(0, 0, resWidth, resHeight);
            if (currentScreen) currentScreen->onResize(resWidth, resHeight);
        }
        // TODO: Create a Key Handler
        else if (event.type == sf::Event::KeyPressed) {
            if(event.key.code == sf::Keyboard::Q || 
               event.key.code == sf::Keyboard::Escape) {

                isRunning = false;
            }
        }
        // TODO: Dispatch the events to the client classes
    }
}

// ============================================== //

/**
 * Initialize the game, set up the context, read configs and do
 * anything needed before the game starts to run.
 */
void Initialize() {
    // TODO: Load Configs

    // Initialize GLEW and check for OpenGL 3.2 support
    if ((glewInit() != GLEW_OK) || (!GLEW_VERSION_3_2)) {
        // TODO: Add better error handling here!
        exit(1);
    }
    std::cout << "Using GLEW: " << glewGetString(GLEW_VERSION) << std::endl;

    // Reset the clock
    clock.restart();

    // Create the windows (and the underlying GL Context)
    window.create(
        sf::VideoMode(resWidth, resHeight),
        windowTitle,
        sf::Style::Close | sf::Style::Resize
    );
    
    // Set some OpenGL stuff up!
    // TODO: is glViewport call necessary??
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glViewport(0, 0, resWidth, resHeight);
    
    // TODO: Set up the initial game state
    currentScreen = new GameScreen();
    std::cout << "Created screen" << std::endl;
}

// ============================================== //

/*
 * Run the game. The game loop is inside here.
 */
void Run() {

    // Define some important control variables
    sf::Time elapsed = sf::milliseconds(0);
    int skippedFrames = 0;

    // Restart the clock
    clock.restart();

    // This is the main loop
    isRunning = true;
    while( isRunning ) {

        // Reset the clock, the frame skip count and
        // sum the elapsed time
        skippedFrames = 0;
        elapsed += clock.restart();

        // If enough time has passed we should update the game state, unless
        // we have skipped more frames than the limit, in which case we skip
        // the update and draw
        while( elapsed > kTickDuration &&
                skippedFrames < kMaxFrameSkip)
        {
            // Handle events, update the game, count the (possibly) skipped 
            // frame and adjust the time elapsed to account for the current
            // tick, trying to keep a constant game update rate
            HandleEvents();
            Step();
            elapsed -= kTickDuration;
            skippedFrames++;
        }

        // Draw a new frame with the current game state
        Draw();

        // Super trick to avoid waisting so much CPU time
        // Of course, this limit our FPS (max=980 FPS)
        // since we must sleep for one milisecond
        // In practice it doesn't hurt that much.
        sf::sleep(sf::milliseconds(2));
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
    if (window.isOpen()) window.close();
}

// ============================================== //

} /* BreakAll */

