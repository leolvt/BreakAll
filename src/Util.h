#ifndef BREAKALL_UTIL_H_INCLUDED
#define BREAKALL_UTIL_H_INCLUDED

#include <string>

// ============================================== //

namespace BreakAll {

std::string ReadFile(const std::string filename);
void PrintLog(GLuint object);
GLuint CreateShader(const std::string filename, GLenum type);

}; /* Breakall*/

// ============================================== //

#endif /* BREAKALL_UTIL_H_INCLUDED */
