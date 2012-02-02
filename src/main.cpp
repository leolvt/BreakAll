#include <iostream>
#include <GL/glew.h>
#include <GL/glfw.h>
using namespace std;

void draw()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5, 5, 5,   0, 0, 0,   0, 1, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 800.0/600.0, 1, 100);
    glMatrixMode(GL_MODELVIEW);

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


    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    // left, right, top, bottom
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //gluLookAt(0, 0, 5,   0, 0, 0,   0, 1, 0);

    //glTranslated(1, 1, 0);
    //glScalef(2,2,2);

    glBegin(GL_TRIANGLES);
        glColor3f(1, 0.1, 1);
        glVertex2d(-1,   -1);
        glVertex2d(-1,   -0.8);
        glVertex2d(-0.8, -1);
    glEnd();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}



int main()
{
    cout << "Hello World!" << endl;

    glfwInit();
    glfwOpenWindow( 800, 600, 8, 8, 8, 8, 8, 0, GLFW_WINDOW);
    bool running = true;
    glEnable(GL_DEPTH_TEST);
    while (running)
    {
        //glClearColor(0.3, 0.3, 0.3, 0.3);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        draw();

        glfwSwapBuffers();

        running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);

    }

    glfwTerminate();

    return 0;
}
