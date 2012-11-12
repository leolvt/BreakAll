#include <vector>
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

    // Store the level area
    m_width = width;
    m_height = height;
    m_aspect = (float)width / height;
    std::cout << "Aspect: " << m_aspect << std::endl;

	// Create the bottom panel and the brick walls
	createBottomPanel();
	createWalls(5, 5, 7);

    // Compute the Model, View and Projection
	m_model = glm::mat4(1.0f);
    m_view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 1.0f), // eye
        glm::vec3(0.0f, 0.0f, 0.0f), // center
        glm::vec3(0.0f, 1.0f, 0.0f)  // up
    );
	m_projection = glm::frustum(
		-m_aspect, m_aspect,
		-1.0f, 1.0f,
		1.0f, 40.0f
	);
	//m_projection = glm::ortho(-m_aspect, m_aspect, -1.0f, 1.0f, 0.0f, 40.0f);
}

// ============================================== //

/**
 * Create the bottom panel which holds the information
 * of the current level
 */
void Level::createBottomPanel() {

	// Compute the aspect ration and the pannel height
	m_bottom_panel_height = 0.15f;
	float height = -1.0f + m_bottom_panel_height;

    // Define the vertices of the panel
    GLfloat vertices[] = {
         m_aspect, height, 2.0f, 1.0f,   0.60f, 0.20f, 0.10f, 1.0f,
         m_aspect, -1.0f,  2.0f, 1.0f,   0.60f, 0.20f, 0.10f, 1.0f,
        -m_aspect, height, 2.0f, 1.0f,   0.60f, 0.20f, 0.10f, 1.0f,
        -m_aspect, -1.0f,  2.0f, 1.0f,   0.60f, 0.20f, 0.10f, 1.0f,
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
 * Create 'count' walls of 'rows' x 'cols' bricks.
 */
void Level::createWalls(int count, int rows, int cols) {

	// Compute brick size
	float xSpace = 0.05f;
	float ySpace = 0.05f;
	float brickWidthMax = (2.0 * (m_aspect-xSpace)) / cols;
	float brickHeightMax = (1.0 - 2*ySpace) / rows;
	float brickLengthMax = brickHeightMax;
	float xScaling = 0.8f;
	float yScaling = 0.9f;
	float zScaling = 0.8f;
	float brickWidth = xScaling * brickWidthMax;
	float brickHeight = yScaling * brickHeightMax;
	float brickLength = zScaling * brickLengthMax ;

	// Initial offsets
	float xOffset = -m_aspect + xSpace + brickWidthMax/2;
	float yOffset = 1 - ySpace - brickHeightMax/2;
	float zOffset = -(brickLengthMax / 2);

	// Print the size and offsets
	std::cout << "*** xOffset: " << xOffset;
	std::cout << ", yOffset: " << yOffset;
	std::cout << ", zOffset: " << zOffset << std::endl;
	std::cout << "*** MaxWidth: " << brickWidthMax;
	std::cout << ", MaxHeight: " << brickHeightMax;
	std::cout << ", MaxLength: " << brickLengthMax << std::endl;

	// Create the bricks
	glm::vec3 size(brickWidth, brickHeight, brickLength);
	for (int wall = 0; wall < count; ++wall) {
		Wall w;
		for (int row = 0; row < rows; ++row) {
			for (int col = 0; col < cols; ++col) {
				glm::vec3 position(xOffset, yOffset, zOffset);
				w.push_back(new Brick(size, position));
				xOffset += brickWidthMax;
				//std::cout << "Brick " << row << ", " << col << std::endl;
				//std::cout << "   Size: " << size.x << ", " << size.y << ", " << size.z << std::endl;
				//std::cout << "   Position: " << position.x << ", " << position.y << ", " << position.z << std::endl;
			}
			// Update the offsets: Go back to the first column, and forward to
			// the next row
			xOffset = -m_aspect + xSpace + brickWidthMax/2;
			yOffset -= brickHeightMax;
		}
		// Store the new wall
		m_walls.push_back(w);

		// Update the offsets: Go back to the first row and column and forward
		// to the next wall
		xOffset = -m_aspect + xSpace + brickWidthMax/2;
		yOffset = 1 - ySpace - brickHeightMax/2;
		zOffset -= brickLength;
	}

}

// ============================================== //

/**
 * Destructor
 */
Level::~Level() {
	// delete the bricks
	for (Wall& wall : m_walls) {
		for (Brick* b : wall) {
			if (b) delete b;
		}
		wall.clear();
	}
	m_walls.clear();

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
	//if (brick) brick->step();
	for (Brick* b: bricks) {
		if (b) b->step();
	}
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
	for (Wall& wall: m_walls) {
		for (Brick* b: wall) {
			SetMVP(b->getModelMatrix(), m_view, m_projection);
			b->draw();
		}
	}
}

// ============================================== //

} /* BreakAll */
