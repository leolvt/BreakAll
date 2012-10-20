#include <iostream>

#include <GL/glew.h>

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Util.h"
#include "Level.h"
#include "BreakAll.h"
#include "GameScreen.h"

namespace BreakAll {

// ============================================== //

/**
 * Default constructor
 */
GameScreen::GameScreen(int width, int height) {

    // Set the screen size and ratio
    m_width = width;
    m_height = height;
    m_aspect = (float) m_width / m_height;
	m_top_panel_height = m_height * 0.1;
	std::cout << "Game Screen Height = " << m_height << std::endl;;
	std::cout << "Top Panel Height = " << m_top_panel_height << std::endl;;

	// Create the Top Panel
	createTopPanel();

    // Create the level
    m_level = new Level(m_width, m_height - m_top_panel_height);
}

// ============================================== //

/**
 * Create the structure used to draw the top panel
 */
void GameScreen::createTopPanel() {

    // Define the vertices of the top panel
	float yVal = 1.0 - 2.0 * m_top_panel_height / m_height;
    GLubyte indices[] = {0, 1, 3, 2};
    GLfloat vertices[] = {
        -m_aspect, 1.0f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f, 1.0f,
         m_aspect, 1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f, 1.0f,
         m_aspect, yVal, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f, 1.0f,
        -m_aspect, yVal, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f, 1.0f,
    };

    // Discard previous errors
    glGetError();

    // Generate the Vertex Array Object
    // and bind it
    glGenVertexArrays(1, &m_vao_top_panel);
    glBindVertexArray(m_vao_top_panel);

    // Generate the Vertex Buffer Object, bind it fill it with data
    glGenBuffers(1, &m_vbo_top_panel);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_top_panel);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Define the data layout (coordinates and colors)
    // Params:  Attrib., Size, Type, Norm., Stride, Offset)
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
            (GLvoid*) (4 * sizeof(GLfloat)));

    // Generate the index buffer object, bind it and fill with data
    glGenBuffers(1, &m_ibo_top_panel);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_top_panel);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
            GL_STATIC_DRAW);

    // Check for OpenGL errors
    GLenum ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        std::cerr << "ERROR: Top Panel: Could not create a VBO: ";
        std::cerr << gluErrorString(ErrorCheckValue) << std::endl;
        throw OpenGLError;
    }

    // Unbind the buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Compute the Model, View and Projection
    model = glm::mat4(1.0f);
    view = glm::mat4(1.0f);
    projection = glm::ortho(-m_aspect, m_aspect, -1.0f, 1.0f);
}

// ============================================== //

/**
 * Destructor
 */
GameScreen::~GameScreen() {
    // Delete the level
    if (m_level) delete m_level;

    // Unbind the vertices
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Delete the buffers
    glDeleteBuffers(1, &m_vbo_top_panel);
    glDeleteBuffers(1, &m_ibo_top_panel);
    glDeleteVertexArrays(1, &m_vao_top_panel);
}

// ============================================== //

/**
 * Update the logic behind the game scene
 */
void GameScreen::step() {
    if (m_level) m_level->step();
}

// ============================================== //

/**
 * Draw the top panel, with game-wide information
 */
void GameScreen::drawTopPanel() {

    // Bind the buffers and activate the attributes
    glBindVertexArray(m_vao_top_panel);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_top_panel);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_top_panel);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // Set the current ModelViewProjection Matrix
    SetMVP(model, view, projection);

    // Draw the vertices
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, 0);

    // Disable the attributes and unbind the buffers
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

// ============================================== //

/**
 * Trigger the drawing of the current level
 */
void GameScreen::drawLevel() {
    if (m_level) m_level->draw();
}

// ============================================== //

/**
 * Draw the current game scene
 */
void GameScreen::draw() {
	// Draw the level in the specified area
	glViewport(0, 0, m_width, m_height-m_top_panel_height);
    drawLevel();
	// Draw the top panel
	glViewport(0, 0, m_width, m_height);
    drawTopPanel();
}

// ============================================== //

} /* BreakAll */

