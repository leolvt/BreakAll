#include <iostream>

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

#include "Brick.h"
#include "BreakAll.h"

#include <glm/gtc/matrix_transform.hpp>

namespace BreakAll {

// ============================================== //

/**
 * Create the VAO, VBO and IBO which will be used by all bricks
 */
GLuint Brick::s_vao = 0;
GLuint Brick::s_vbo = 0;
GLuint Brick::s_ibo = 0;
int Brick::s_num_bricks = 0;

// ============================================== //

void Brick::CreateGLObjects() {

	std::cerr << "Criando Brick" << std::endl;

	// Define the vertices and indexes of the brick
	GLubyte indices[] = {
		0, 1, 2, 3, 1, 5, 3, 6 ,7 ,5, 4, 1, 0, 4, 2, 7, 3, // Cube Surface
		0, 1, 3, 2, 0, 4, 7, 2, 3, 6, 7, 6, 5, 4, 5, 1,    // Cuve Edges
	};
	GLfloat vertices[] = {
		1.0f,  1.0f, -1.0f, 1.0f,   0.20f, 0.80f, 0.20f, 1.0f,
		1.0f, -1.0f, -1.0f, 1.0f,   0.20f, 0.80f, 0.20f, 1.0f,
		1.0f,  1.0f,  1.0f, 1.0f,   0.20f, 0.80f, 0.20f, 1.0f,
		1.0f, -1.0f,  1.0f, 1.0f,   0.20f, 0.80f, 0.20f, 1.0f,
		-1.0f,  1.0f, -1.0f, 1.0f,   0.20f, 0.80f, 0.20f, 1.0f,
		-1.0f, -1.0f, -1.0f, 1.0f,   0.20f, 0.80f, 0.20f, 1.0f,
		-1.0f, -1.0f,  1.0f, 1.0f,   0.20f, 0.80f, 0.20f, 1.0f,
		-1.0f,  1.0f,  1.0f, 1.0f,   0.20f, 0.80f, 0.20f, 1.0f,
	};

	// Discard previous errors
	glGetError();

	// Generate and bind the Vertex Array Object
	glGenVertexArrays(1, &s_vao);
	glBindVertexArray(s_vao);

	// Generate, bind and fill the Vertex Buffer Object
	glGenBuffers(1, &s_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, s_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Generate, bind and fill the Index Buffer Object
	glGenBuffers(1, &s_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_ibo);
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

}

// ============================================== //

void Brick::DeleteGLObjects() {
	glDeleteBuffers(1, &s_vbo);
	glDeleteBuffers(1, &s_ibo);
	glDeleteVertexArrays(1, &s_vao);
}

// ============================================== //

/**
 * Create a Brick with a given height, width and length
 */
Brick::Brick(glm::vec3 size, glm::vec3 position) {
	// Create and scale the model matrix
	m_position = position;
	m_scale = size / 2.0f;
	m_model = glm::mat4(1.0f);
	m_model = glm::translate(m_model, m_position);
	m_model = glm::scale(m_model, m_scale);

	// We only create the brick GL objects (VAO, VBO, IBO) if we
	// haven't created them yet
	if (s_num_bricks++ == 0) CreateGLObjects();

}

// ============================================== //

/**
 * Destructor
 */
Brick::~Brick() {
	if (--s_num_bricks == 0) DeleteGLObjects();
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
}

// ============================================== //

/**
 * Draw the brick
 */
void Brick::draw() {

    // Bind the buffers and activate the attributes
    glBindVertexArray(s_vao);
    glBindBuffer(GL_ARRAY_BUFFER, s_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_ibo);
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
