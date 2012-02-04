#ifndef BREAKALL_H
#define BREAKALL_H

// ============================================== //

namespace BreakAll 
{
    void Initialize();
    void Run();
    void Terminate();

    typedef enum 
    {
        KEY_ESC
    } Key;
    
    typedef enum 
    {
        KEY_PRESSED,
        KEY_RELEASED
    } KeyAction;

} /* BreakAll */

// ============================================== //

#endif /* BREAKALL_H */
