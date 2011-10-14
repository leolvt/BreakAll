#ifndef MODE_H_INCLUDED
#define MODE_H_INCLUDED

#include <GL/glew.h>
#include <GL/glfw.h>

#define OGLFT_NO_SOLID 1
#define OGLFT_NO_QT 1
#include <oglft/OGLFT.h>

namespace BreakAll {

// ========================== //

typedef struct 
{
    float top;
    float right;
    float bottom;
    float left;
} Area;

// ========================== //

class Drawable
{
    public:
        virtual void update() = 0;
        virtual void draw() = 0;
        virtual void onKeyPressed(int key) = 0;
        virtual void onMouseMove(float x, float y) = 0;
};

// ========================== //

}; // namespace BreakAll

#endif  /* MODE_H_INCLUDED */

