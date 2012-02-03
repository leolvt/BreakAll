#ifndef ENGINE_H
#define ENGINE_H

#include <string>

// ============================================== //

class Engine {
    public:
        virtual void OpenWindow(int width, int height, std::string title) = 0;
        virtual void OpenFullScreenWindow(int width, int height, std::string title) = 0;
        virtual void SwapBuffers() = 0;
        virtual double GetTime() = 0;
        virtual void SetTime(double time) = 0;

        virtual void ClearScreen() = 0;
};

// ============================================== //

#endif /* ENGINE_H */
