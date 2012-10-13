#include <iostream>

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include "BreakAll.h"
#include "GameScreen.h"

namespace BreakAll {

// ============================================== //

/**
 * Default constructor
 */    
GameScreen::GameScreen() {
}

// ============================================== //

/**
 * Default destructor
 */
GameScreen::~GameScreen() {

}

// ============================================== //

void GameScreen::onResize(int width, int height) {

    // Only make changes the size is changed
    // TODO: Consider moving this to the outer Event Handler
    //if ((width != m_screen_width) || (height != m_screen_height)) {
    //}
}

// ============================================== //
 
/**
 * Update the logic behind the game scene
 */
void GameScreen::step() {
    //int t = 5;
    //m_degree += (1.0/50.0) * 360/t;
    //while (m_degree > 360) m_degree -= 360;
}

// ============================================== //

/**
 * Draw the top panle, with game-wide information
 */
void GameScreen::drawTopPanel() {

}

// ============================================== //

/**
 * Trigger the drawing of the current level
 */
void GameScreen::drawLevel() {

}

// ============================================== //
    
/**
 * Draw the current game scene
 */
void GameScreen::draw() {
    drawTopPanel();
    drawLevel();
}

// ============================================== //
    
} /* BreakAll */

