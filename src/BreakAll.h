#ifndef BREAKALL_H_INCLUDED
#define BREAKALL_H_INCLUDED

#include <SFML/Graphics.hpp>

// ============================================== //

namespace BreakAll
{
    void Initialize();
    void Run();
    void Terminate();
    sf::RenderWindow& GetWindow();

} /* BreakAll */

// ============================================== //

#endif /* BREAKALL_H_INCLUDED */
