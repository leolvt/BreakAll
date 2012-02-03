#ifndef OPENGL_ENGINE_H
#define OPENGL_ENGINE_H

#include "Engine.h"

// ============================================== //

class OpenGLEngine : public Engine 
{
    public:
        OpenGLEngine ();
        ~OpenGLEngine();
        
        void OpenWindow(int width, int height, std::string title);
        void OpenFullScreenWindow(int width, int height, std::string title);
        void SwapBuffers();
        double GetTime();
        void SetTime(double time);
        
        void ClearScreen();
};

// ============================================== //

#endif /* OPENGL_ENGINE_H */
