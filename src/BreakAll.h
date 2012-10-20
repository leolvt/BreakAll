#ifndef BREAKALL_H_INCLUDED
#define BREAKALL_H_INCLUDED

#include <glm/glm.hpp>

// ============================================== //

namespace BreakAll
{

// ============================================== //

typedef enum {
    OpenGLError,
    GLEWError,
} Errors;

void Initialize();
void Run();
void Terminate();
void SetMVP(glm::mat4 model, glm::mat4 view, glm::mat4 projection);

// ============================================== //

} /* BreakAll */

// ============================================== //

#endif /* BREAKALL_H_INCLUDED */
