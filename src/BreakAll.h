#ifndef BREAKALL_H_INCLUDED
#define BREAKALL_H_INCLUDED

#include "Mode.h"

// ========================== //

class BreakAll
{
    public:
        BreakAll();
        virtual ~BreakAll();
        virtual void run();
    private:
        Mode* currentMode;
};

// ========================== //

#endif  /* BREAKALL_H_INCLUDED */

