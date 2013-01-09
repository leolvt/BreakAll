#ifndef BREAKALL_LEVEL_H_INCLUDED
#define BREAKALL_LEVEL_H_INCLUDED

#include <vector>

#include <glm/glm.hpp>

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

// ============================================== //

namespace BreakAll {

class Brick;
class Ball;
typedef std::vector<Brick*> Wall;

// ============================================== //

class Level {
    public:
        Level(int width, int height);
        virtual ~Level();
        virtual void step();
        virtual void draw();
    private:

		void createBall();
		void createBottomPanel();
		void createWalls(int count, int rows, int cols);
		void drawBottomBar();

        int m_width;
        int m_height;
		float m_bottom_panel_height;
        float m_aspect;

        GLuint m_vao_bottom_panel;
        GLuint m_vbo_bottom_panel;
        GLuint m_ibo_bottom_panel;
		Ball* m_ball;
		std::vector<Brick*> bricks;
		std::vector<Wall> m_walls;

        glm::mat4 m_model;
        glm::mat4 m_view;
        glm::mat4 m_projection;

};

// ============================================== //

} /* BreakAll */

// ============================================== //

#endif /* BREAKALL_LEVEL_H_INCLUDED */
