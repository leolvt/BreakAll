#ifndef BREAKALL_BALL_H_INCLUDED
#define BREAKALL_BALL_H_INCLUDED

#include <glm/glm.hpp>

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

// ============================================== //

namespace BreakAll {

// ============================================== //

class Ball {
	public:
		Ball(float radius, glm::vec3 position);
		Ball(glm::vec3 params, glm::vec3 position);
		virtual ~Ball();
		virtual void step();
		virtual void draw();
		glm::mat4 getModelMatrix();

	private:
		static void CreateGLObjects();
		static void DeleteGLObjects();
		static int s_num_balls;
		static GLuint s_vao;
		static GLuint s_vbo;
		static GLuint s_ibo;

		glm::vec3 m_scale;
		glm::vec3 m_position;
		glm::mat4 m_model;
};

// ============================================== //

} /* BreakAll */

// ============================================== //

#endif /* BREAKALL_BALL_H_INCLUDED */
