#ifndef BREAKALL_GAMESCREEN_H_INCLUDED
#define BREAKALL_GAMESCREEN_H_INCLUDED

#include <glm/glm.hpp>

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

// ============================================== //

namespace BreakAll {

class Level;

// ============================================== //

class GameScreen {
    public:
        GameScreen(int width, int height);
        virtual ~GameScreen();
        virtual void step();
        virtual void draw();

    private:
		void createTopPanel();
        void drawTopPanel();
        void drawLevel();

        GLuint m_vao_top_panel;
        GLuint m_vbo_top_panel;
        GLuint m_ibo_top_panel;

        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;

        int m_width;
        int m_height;
		int m_top_panel_height;
		float m_aspect;
        Level* m_level;
};

// ============================================== //

} /* BreakAll */

// ============================================== //

#endif /* BREAKALL_GAMESCREEN_H_INCLUDED */
