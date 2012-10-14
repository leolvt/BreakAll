#include <iostream>

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include "Level.h"
#include "BreakAll.h"
#include "GameScreen.h"

namespace BreakAll {

// ============================================== //

/**
 * Default constructor
 */    
GameScreen::GameScreen() {
    m_level = new Level();
    m_width = 13;
    m_height = 10;

    // Define the vertices of the top panel
    GLubyte indices[] = {0, 1, 3, 2};
    GLfloat vertices[] = {
        -1.3f, 1.0f, 0.0f, 1.0f,   0.8f, 0.2f, 0.4f, 1.0f,
         1.3f, 1.0f, 0.0f, 1.0f,   0.8f, 0.2f, 0.4f, 1.0f,
         1.3f, 0.9f, 0.0f, 1.0f,   0.8f, 0.2f, 0.4f, 1.0f,
        -1.3f, 0.9f, 0.0f, 1.0f,   0.8f, 0.2f, 0.4f, 1.0f,
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
        std::cerr << "ERROR: Could not create a VBO: ";
        std::cerr << gluErrorString(ErrorCheckValue) << std::endl;
        exit(-1); // TODO: Throw exception
    }
    
    // Unbind the buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// ============================================== //

/**
 * Default destructor
 */
GameScreen::~GameScreen() {
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
 * Update the internal state with the new size of the screen
 */
void GameScreen::onResize(int width, int height) {
    if ((m_width != width) || (m_height != height)) {
        m_width = width;
        m_height = height;
        std::cout << "Changed to: " << width << "x" << m_height << std::endl;
        
        // Update the vertices
        float aspect = (float)m_width/m_height;
        GLfloat vertices[] = {
            -aspect, 1.0f, 0.0f, 1.0f,   0.8f, 0.2f, 0.4f, 1.0f,
             aspect, 1.0f, 0.0f, 1.0f,   0.8f, 0.2f, 0.4f, 1.0f,
             aspect, 0.9f, 0.0f, 1.0f,   0.8f, 0.2f, 0.4f, 1.0f,
            -aspect, 0.9f, 0.0f, 1.0f,   0.8f, 0.2f, 0.4f, 1.0f,
        };
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo_top_panel);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, 
                GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
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
    float topPanelHeight = m_height * 0.1;
    float aspect = (float)m_width / m_height;

    // Bind the buffers and activate the attributes
    glBindVertexArray(m_vao_top_panel);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_top_panel);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_top_panel);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // Draw the vertices
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, 0);

    // Disable the attributes and unbind the buffers
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
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
    drawTopPanel();
    drawLevel();
}

// ============================================== //
    
} /* BreakAll */

