#include <iostream>

#include <GL/glew.h>

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Level.h"
#include "Brick.h"
#include "BreakAll.h"

namespace BreakAll {

// ============================================== //

/**
 * Default constructor
 */
Level::Level(int width, int height) {

	// Create a brick
	createBottomPanel();
	brick = new Brick(
		glm::vec3(0.6, 0.3, 0.3), // size
		glm::vec3(0.0, 0.0, 0.0) // position
	);

    // Store the level area
    m_width = width;
    m_height = height;
    m_aspect = (float)width / height;
    std::cout << "Aspect: " << m_aspect << std::endl;

    // Compute the Model, View and Projection
	model = glm::mat4(1.0f);
    view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 3.0f), // eye
        glm::vec3(0.0f, 0.0f, 0.0f), // center
        glm::vec3(0.0f, 1.0f, 0.0f)  // up
    );
	projection = glm::frustum(
		-m_aspect, m_aspect,
		-1.0f, 1.0f,
		2.0f, 40.0f
	);
}

// ============================================== //

/**
 * Create the bottom panel which holds the information
 * of the current level
 */
void Level::createBottomPanel() {

	// Compute the aspect ration and the pannel height
    float aspect = (float)m_width / m_height;
	float height = -1.0f + 0.15f;

    // Define the vertices of the panel
    GLfloat vertices[] = {
         aspect, height, 2.0f, 1.0f,   0.60f, 0.20f, 0.10f, 1.0f,
         aspect, -1.0f,  2.0f, 1.0f,   0.60f, 0.20f, 0.10f, 1.0f,
        -aspect, height, 2.0f, 1.0f,   0.60f, 0.20f, 0.10f, 1.0f,
        -aspect, -1.0f,  2.0f, 1.0f,   0.60f, 0.20f, 0.10f, 1.0f,
    };

    // Discard previous errors
    glGetError();

    // Generate the Vertex Array Object
    // and bind it
    glGenVertexArrays(1, &m_vao_bottom_panel);
    glBindVertexArray(m_vao_bottom_panel);

    // Generate the Vertex Buffer Object, bind it fill it with data
    glGenBuffers(1, &m_vbo_bottom_panel);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_bottom_panel);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Define the data layout (coordinates and colors)
    // Params:  Attrib., Size, Type, Norm., Stride, Offset)
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
            (GLvoid*) (4 * sizeof(GLfloat)));

    // Check for OpenGL errors
    GLenum ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        std::cerr << "ERROR: Bottom Panel: Could not create a VBO: ";
        std::cerr << gluErrorString(ErrorCheckValue) << std::endl;
        throw OpenGLError;
    }

    // Unbind the buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// ============================================== //

/**
 * Destructor
 */
Level::~Level() {
	if (brick) delete brick;

    // Unbind the vertices
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Delete the buffers (bottom_panel)
	glDeleteBuffers(1, &m_vbo_bottom_panel);
    glDeleteVertexArrays(1, &m_vao_bottom_panel);
}

// ============================================== //

/**
 * Update the logic behind the level
 */
void Level::step() {
	if (brick) brick->step();
}

// ============================================== //

/**
 * Draw the bottom bar with the current level information
 */
void Level::drawBottomBar() {
    // Bind the buffers and activate the attributes
    glBindVertexArray(m_vao_bottom_panel);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_bottom_panel);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // Set the current ModelViewProjection Matrix
    SetMVP(glm::mat4(1.0f), glm::mat4(1.0f), 
		   glm::ortho(-m_aspect, m_aspect, -1.0f, 1.0f, -2.0f, 0.0f));

    // Draw the vertices
    SetColorFact(1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // Disable the attributes and unbind the buffers
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// ============================================== //

/**
 * Draw the current level
 */
void Level::draw() {

	drawBottomBar();
	if (brick) {
		glm::mat4 brickModel = brick->getModelMatrix();
		SetMVP(brickModel, view, projection);
		brick->draw();
	}
}

// ============================================== //

} /* BreakAll */
