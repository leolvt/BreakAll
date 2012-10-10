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

    private:
        float degree_;
};

// ============================================== //

} /* BreakAll */

// ============================================== //

#endif /* BREAKALL_GAMESCREEN_H_INCLUDED */
