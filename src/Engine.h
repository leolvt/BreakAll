#ifndef ENGINE_H
#define ENGINE_H

#include <string>

// ============================================== //

namespace Engine
{
    typedef enum
    {
        KEY_ESC,
    } Key;
    
    typedef enum
    {
        KEY_PRESSED,
        KEY_RELEASED
    } KeyState;

    typedef void (*OnKeyEvent)(Key,KeyState);

    void Init();
    void Terminate();

    void OpenWindow(int width, int height, std::string title);
    void OpenFullScreenWindow(int width, int height, std::string title);
    void SwapBuffers();
    double GetTime();
    void SetTime(double time);

    void PollEvents();
    bool IsWindowOpen();
    void ClearScreen();
    void SetKeyCallback(OnKeyEvent e);
};

// ============================================== //

#endif /* ENGINE_H */
