#define OGLFT_NO_SOLID 1
#define OGLFT_NO_QT 1

#include <GL/glew.h>
#include <GL/glfw.h>
#include <oglft/OGLFT.h>

#include <iostream>

int main(int argc, const char *argv[]) 
{
    glfwInit();
    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, 1);
    glfwOpenWindow(800,600, 8,8,8,0, 0,0, GLFW_WINDOW);
    glewInit();

//    OGLFT::Filled* face = new OGLFT::Filled(
    OGLFT::Monochrome* face = new OGLFT::Monochrome(
            "/usr/share/fonts/truetype/ttf-dejavu/DejaVuSans.ttf",
            13
    );
    std::cout << "Font height: " << face->height() << std::endl;;

    // Always check to make sure the face was properly constructed
    if ( face == 0 || !face->isValid() ) {
        std::cerr << "Could not construct face."  << std::endl;
        return 0;
    }

    face->setForegroundColor(0,0,0);
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

    bool run = true;
//    glViewport(200,100,400,400);
    glClearColor( 0.0, 1.0, 1.0, 1.0 );
    while (run)
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_QUADS);
            glColor3f(1.0,1.0,1.0);
            glVertex2f(-1.0, -0.9);
            glVertex2f(-1.0, 0.9);
            glVertex2f(1.0, 0.9);
            glVertex2f(1.0, -0.9);
        glEnd();
       
        OGLFT::BBox bb = face->measure("Teste de Fonte");
        std::cout << (bb.y_max_ - bb.y_min_) << std::endl;
        face->draw(-0.95,-0.97333, "Teste de Fonte");

        run= !glfwGetKey( GLFW_KEY_ESC ) &&
            glfwGetWindowParam( GLFW_OPENED );

        glfwSwapBuffers();
        glfwSleep(0.02);
    }

    glfwTerminate();

    std::cout << "Hello World!" << std::endl;
    return 0;
}
