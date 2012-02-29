#include <iostream>

//#include "BreakAll.h"
#include <GL/glew.h>

int main()
{
    /*
    std::cout << "Hello World!" << std::endl;
    BreakAll::Initialize();
    BreakAll::Run();
    BreakAll::Terminate();
    */
    glBegin(GL_TRIANGLES);
        glColor3f(1, 0.1, 0.1);
        glVertex3d( 0,  1,  0);
        glVertex3d(-1,  0,  1);
        glVertex3d( 1,  0,  1);

        glColor3f(0.1, 1, 0.1);
        glVertex3d( 0,  1,  0);
        glVertex3d( 1,  0,  1);
        glVertex3d( 1,  0, -1);

        glColor3f(0.1, 0.1, 1);
        glVertex3d( 0,  1,  0);
        glVertex3d(-1,  0,  1);
        glVertex3d(-1,  0, -1);

        glColor3f(0.1, 1, 1);
        glVertex3d( 0,  1,  0);
        glVertex3d(-1,  0, -1);
        glVertex3d( 1,  0, -1);

        glColor3f(1, 1, 0.1);
        glVertex3d(-1,  0,  1);
        glVertex3d(-1,  0, -1);
        glVertex3d( 1,  0, -1);
        glVertex3d( 1,  0, -1);
        glVertex3d( 1,  0,  1);
        glVertex3d(-1,  0,  1);
    glEnd();
    return 0;
}
