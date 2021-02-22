
#include "error.hpp"

bool GLPrintError(const char *funct, const char *file, int line)
{
    while (GLuint err = glGetError())
    {
        ERR("[OpenGL Error] (" << err << ") " << funct << " " << file << ":" << line);
        return false;
    }
    return true;
}

void GLClearError()
{
    while (glGetError())
        ;
}
