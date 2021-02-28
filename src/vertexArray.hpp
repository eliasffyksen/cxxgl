#pragma once

#include <vector>
#include <GL/glew.h>

#include "error.hpp"
#include "buffer.hpp"
#include "vertexBufferLayout.hpp"

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;

    void addBuffer(Buffer& vertexBuffer, VertexBufferLayout& vbl);

private:
    GLuint id;
};