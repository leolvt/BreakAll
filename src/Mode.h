#ifndef MODE_H_INCLUDED
#define MODE_H_INCLUDED

// ========================== //

class Mode
{
    public:
        virtual void update() = 0;
        virtual void draw() = 0;
        virtual void onKeyChange(int key, int status) = 0;
        virtual void onMouseChange(float x, float y) = 0;
};

// ========================== //

#endif  /* MODE_H_INCLUDED */

