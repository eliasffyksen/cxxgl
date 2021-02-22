
#include "error.hpp"

void GLPrintError() {
    while (GLuint err = glGetError()) {
       FATAL_ERR("[OpenGL Error] (" << err << ")");
    }
}

void GLClearError() {
    while(glGetError());
}
