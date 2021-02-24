
#pragma once

#include <GL/glew.h>
#include <vector>

#include "error.hpp"

class Buffer
{
public:
    Buffer(const void* data, size_t size, GLenum bufferType = GL_ARRAY_BUFFER, GLenum usage = GL_STATIC_DRAW);
    ~Buffer();

    void bind();
    void unbind();
    GLuint getId();
private:
    GLuint id;
    GLenum bufferType;
};
