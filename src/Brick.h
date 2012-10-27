#ifndef BREAKALL_BRICK_H_INCLUDED
#define BREAKALL_BRICK_H_INCLUDED

#include <glm/glm.hpp>

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

// ============================================== //

namespace BreakAll {

// ============================================== //

class Brick {
    public:
        Brick(glm::vec3 size, glm::vec3 position);
        virtual ~Brick();
        virtual void step();
        virtual void draw();
		glm::mat4 getModelMatrix();

    private:
		static void CreateGLObjects();
		static void DeleteGLObjects();
		static int s_num_bricks;
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

#endif /* BREAKALL_BRICK_H_INCLUDED */
