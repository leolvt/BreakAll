#ifndef BREAKALL_GAMESCREEN_H_INCLUDED
#define BREAKALL_GAMESCREEN_H_INCLUDED

// ============================================== //

namespace BreakAll {

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
};

// ============================================== //

} /* BreakAll */

// ============================================== //

#endif /* BREAKALL_GAMESCREEN_H_INCLUDED */
