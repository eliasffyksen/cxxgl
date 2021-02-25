
#include "vertexBufferLayout.hpp"

GLuint VertexArrayAttrib::getTypeSize()
{
    switch (type)
    {
        case GL_FLOAT: return sizeof(GLfloat);
        case GL_UNSIGNED_INT: return sizeof(GLuint);
        case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
        default: FATAL_ERR("Unknown type in vertex attrib");
    }
    return 0;
}
