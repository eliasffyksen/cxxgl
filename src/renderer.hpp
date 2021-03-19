#pragma once

#include <GL/glew.h>

#include "vertexArray.hpp"
#include "buffer.hpp"
#include "shader.hpp"
#include "error.hpp"

class Renderer
{
public:
    void clear();
    void draw(const VertexArray& vao, const Buffer& ibo, const Shader& shader, GLenum mode=GL_TRIANGLES);
};
