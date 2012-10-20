#ifndef BREAKALL_LEVEL_H_INCLUDED
#define BREAKALL_LEVEL_H_INCLUDED

#include <glm/glm.hpp>

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

// ============================================== //

namespace BreakAll {

class Brick;

// ============================================== //

class Level {
    public:
        Level(int width, int height);
        virtual ~Level();
        virtual void step();
        virtual void draw();
    private:
		void createBottomPanel();
		void drawBottomBar();

        int m_width;
        int m_height;
        float m_aspect;
        glm::vec3 m_degree;

        GLuint m_vao_box;
        GLuint m_vbo_box;
        GLuint m_ibo_box;

        GLuint m_vao_bottom_panel;
        GLuint m_vbo_bottom_panel;
        GLuint m_ibo_bottom_panel;
		Brick* brick;

        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;

};

// ============================================== //

} /* BreakAll */

// ============================================== //

#endif /* BREAKALL_LEVEL_H_INCLUDED */
