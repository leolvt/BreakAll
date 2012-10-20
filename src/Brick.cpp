#include <iostream>

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

#include "Brick.h"
#include "BreakAll.h"

#include <glm/gtc/matrix_transform.hpp>

namespace BreakAll {

// ============================================== //

/**
 * Create a Brick with a given height, width and length
 */
Brick::Brick(glm::vec3 size, glm::vec3 position) {

    // Define the vertices and indexes of the brick
	GLubyte indices[] = {
		0, 1, 2, 3, 1, 5, 3, 6 ,7 ,5, 4, 1, 0, 4, 2, 7, 3, // Cube Surface
		0, 1, 3, 2, 0, 4, 7, 2, 3, 6, 7, 6, 5, 4, 5, 1,    // Cuve Edges
	};
	GLfloat vertices[] = {
		 1.0f,  1.0f, -1.0f, 1.0f,   1.00f, 0.00f, 0.00f, 1.0f,
		 1.0f, -1.0f, -1.0f, 1.0f,   0.00f, 1.00f, 0.00f, 1.0f,
		 1.0f,  1.0f,  1.0f, 1.0f,   0.00f, 0.00f, 1.00f, 1.0f,
		 1.0f, -1.0f,  1.0f, 1.0f,   1.00f, 1.00f, 0.00f, 1.0f,
		-1.0f,  1.0f, -1.0f, 1.0f,   1.00f, 0.00f, 1.00f, 1.0f,
		-1.0f, -1.0f, -1.0f, 1.0f,   0.00f, 1.00f, 1.00f, 1.0f,
		-1.0f, -1.0f,  1.0f, 1.0f,   1.00f, 1.00f, 1.00f, 1.0f,
		-1.0f,  1.0f,  1.0f, 1.0f,   0.00f, 0.00f, 0.00f, 1.0f,
	};

    // Discard previous errors
    glGetError();

    // Generate and bind the Vertex Array Object
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // Generate, bind and fill the Vertex Buffer Object
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Generate, bind and fill the Index Buffer Object
    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
		GL_STATIC_DRAW);

    // Define the data layout (coordinates and colors)
    // Params:  Attrib., Size, Type, Norm., Stride, Offset)
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
            (GLvoid*) (4 * sizeof(GLfloat)));

    // Check for OpenGL errors
    GLenum ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        std::cerr << "ERROR: Brick: Could not create a VBO: ";
        std::cerr << gluErrorString(ErrorCheckValue) << std::endl;
        throw OpenGLError;
    }

    // Unbind the buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

	// Create and scale the model matrix
    m_degree = glm::vec3(0.0f);
	m_position = position;
	m_scale = size / 2.0f;
	m_model = glm::mat4(1.0f);
	m_model = glm::translate(m_model, m_position);
    m_model = glm::rotate(m_model, m_degree.x, glm::vec3(1.0f, 0.0f, 0.0f));
    m_model = glm::rotate(m_model, m_degree.y, glm::vec3(0.0f, 1.0f, 0.0f));
    m_model = glm::rotate(m_model, m_degree.z, glm::vec3(0.0f, 0.0f, 1.0f));
	m_model = glm::scale(m_model, m_scale);
}

// ============================================== //

/**
 * Destructor
 */
Brick::~Brick() {

}

// ============================================== //

glm::mat4 Brick::getModelMatrix() {

	return m_model;
}

// ============================================== //

/**
 * Update the brick
 */
void Brick::step() {
    m_degree += glm::vec3(
        360.0 / (50 * 10.0),
        360.0 / (50 * 10.0),
        360.0 / (50 * 10.0)
    );
    while (m_degree.x > 360) m_degree.x -= 360;
    while (m_degree.y > 360) m_degree.y -= 360;
    while (m_degree.z > 360) m_degree.z -= 360;

	// Update the model matrix
	m_model = glm::mat4(1.0f);
	m_model = glm::translate(m_model, m_position);
    m_model = glm::rotate(m_model, m_degree.x, glm::vec3(1.0f, 0.0f, 0.0f));
    m_model = glm::rotate(m_model, m_degree.y, glm::vec3(0.0f, 1.0f, 0.0f));
    m_model = glm::rotate(m_model, m_degree.z, glm::vec3(0.0f, 0.0f, 1.0f));
	m_model = glm::scale(m_model, m_scale);
}

// ============================================== //

/**
 * Draw the brick
 */
void Brick::draw() {

    // Bind the buffers and activate the attributes
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // Draw the cube surface
    SetColorFact(1.0f);
	glDrawElements(GL_TRIANGLE_STRIP, 17, GL_UNSIGNED_BYTE, 0);

	// Draw the cube edges
	glLineWidth(2);
    SetColorFact(0.1f);
    glDrawElements(GL_LINE_STRIP, 16, GL_UNSIGNED_BYTE,
				   (GLvoid *) (sizeof(GLubyte)*17));
    SetColorFact(1.0f);

    // Disable the attributes and unbind the buffers
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// ============================================== //

} /* BreakAll */
