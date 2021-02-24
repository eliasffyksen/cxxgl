#pragma once

#include <GL/glew.h>

#include "error.hpp"

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void bind();
    void unbind();

private:
    GLuint id;
};