#ifndef BREAKALL_H_INCLUDED
#define BREAKALL_H_INCLUDED

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

namespace sf {
class RenderWindow;
}

// ============================================== //

namespace BreakAll
{

void Initialize();
void Run();
void Terminate();

GLint GetVertexAttribCoord();

} /* BreakAll */

// ============================================== //

#endif /* BREAKALL_H_INCLUDED */
