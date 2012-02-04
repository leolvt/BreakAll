#ifndef MENU_H
#define MENU_H

#include "Drawable.h"

// ============================================== //

class Menu : public Drawable
{
    public:
        Menu ();
        ~Menu ();
        void Draw();
        void Step();
        void KeyPressed(BreakAll::Key k);
    private:
        /* data */
};

// ============================================== //

#endif /* MENU_H */
