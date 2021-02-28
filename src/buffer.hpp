
#pragma once

#include <GL/glew.h>
#include <vector>

#include "error.hpp"

class Buffer
{
public:
    Buffer(const void* data, size_t size, GLenum bufferType = GL_ARRAY_BUFFER, GLenum usage = GL_STATIC_DRAW);
    ~Buffer();

    void bind() const;
    void unbind() const;
    GLuint getId() const;
    size_t getSize() const;

private:
    GLuint id;
    GLenum bufferType;
    size_t bufferSize;
};
