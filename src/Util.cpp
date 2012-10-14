#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

#include "Util.h"

namespace BreakAll {

// ============================================== //
/**
 * Store all the file's contents in memory, useful to pass shaders
 * source code to OpenGL
 */
std::string ReadFile(const std::string filename) {
    // Open the file
    std::ifstream file(filename);
    file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
    //if ( !file.good() ) return ""; 

    // Read its contents to a string
    std::stringstream sstr;
    sstr << file.rdbuf();
    
    // Close the file
    file.close();
    
    // Return the string
    return sstr.str();
}

// ============================================== //

/**
 * Display compilation errors from the OpenGL shader compiler
 */
void PrintLog(GLuint object)
{
    GLint log_length = 0;
    if (glIsShader(object))
        glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
    else if (glIsProgram(object))
        glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
    else {
        std::cerr << "PrintLog: Not a shader or a program" << std::endl;
        return;
    }

    char* log = new char [log_length];

    if (glIsShader(object))
        glGetShaderInfoLog(object, log_length, NULL, log);
    else if (glIsProgram(object))
        glGetProgramInfoLog(object, log_length, NULL, log);

    std::cerr << log << std::endl;
    delete log;
}

// ============================================== //

/**
 * Compile the shader from file 'filename', with error handling
 */
GLuint CreateShader(const std::string filename, GLenum type)
{
    // Read the file into a string
    std::string source = ReadFile(filename);
    
    // Create the shader and copy to source
    GLuint res = glCreateShader(type);
    const GLchar* sourceContent = source.c_str();
    const GLint sourceSize = source.size();
    glShaderSource(res, 1, &sourceContent, &sourceSize );

    // Compile it
    glCompileShader(res);
    GLint compile_ok = GL_FALSE;
    glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok);

    // If there was an error, print it!
    if (compile_ok == GL_FALSE) {
        std::cerr << filename << ": ";
        PrintLog(res); 
        std::cerr << std::endl;
        glDeleteShader(res);
        return 0;
    }

    return res;
}

// ============================================== //

}; /* BreakAll */

// ============================================== //

