#ifndef MODE_H_INCLUDED
#define MODE_H_INCLUDED

#include "Drawable.h"

namespace BreakAll {

// ========================== //

class Mode: public Drawable
{
    public:
        virtual void update() = 0;
};

// ========================== //

}; // namespace BreakAll;

#endif  /* MODE_H_INCLUDED */

