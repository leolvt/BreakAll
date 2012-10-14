#ifndef BREAKALL_LEVEL_H_INCLUDED
#define BREAKALL_LEVEL_H_INCLUDED

// ============================================== //

namespace BreakAll {

// ============================================== //

class Level {
    public:
        Level();
        virtual ~Level();
        virtual void step();
        virtual void draw();
        virtual void onResize(int width, int height);
};

// ============================================== //

} /* BreakAll */

// ============================================== //

#endif /* BREAKALL_LEVEL_H_INCLUDED */
