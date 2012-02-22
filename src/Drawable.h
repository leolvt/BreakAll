#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "BreakAll.h"

// ============================================== //

class Drawable {
    public:
        virtual void Draw() = 0;
        virtual void Step() = 0;
        virtual void OnKeyPressed(BreakAll::Key k) = 0;
};

// ============================================== //

#endif /* DRAWABLE_H */
