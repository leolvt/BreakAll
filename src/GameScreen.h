#ifndef BREAKALL_GAMESCREEN_H_INCLUDED
#define BREAKALL_GAMESCREEN_H_INCLUDED

// ============================================== //

namespace BreakAll {

class Level;

// ============================================== //

class GameScreen {
    public:
        GameScreen();
        virtual ~GameScreen();
        virtual void step();
        virtual void draw();
        virtual void onResize(int width, int height);

    private:
        void drawTopPanel();
        void drawLevel();

        GLuint m_vao_top_panel;
        GLuint m_vbo_top_panel;
        GLuint m_ibo_top_panel;
        int m_width;
        int m_height;
        Level* m_level;
};

// ============================================== //

} /* BreakAll */

// ============================================== //

#endif /* BREAKALL_GAMESCREEN_H_INCLUDED */
