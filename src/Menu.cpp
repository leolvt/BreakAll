#include "Menu.h"
#include "BreakAll.h"

#include <GL/glew.h>
#include <GL/glfw.h>

// ============================================== //

Menu::Menu ()
{

}

// ============================================== //

Menu::~Menu ()
{

}

// ============================================== //

void Menu::Draw()
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

// ============================================== //

void Menu::Step()
{

}

// ============================================== //

void Menu::OnKeyPressed(BreakAll::Key k)
{
    if (k == BreakAll::KEY_ESC) BreakAll::Stop();
}

// ============================================== //

