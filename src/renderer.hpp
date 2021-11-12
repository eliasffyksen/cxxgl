#pragma once

#include <GL/glew.h>

#include "vertexArray.hpp"
#include "buffer.hpp"
#include "shader.hpp"
#include "error.hpp"

class Renderer
{
public:
    Renderer(GLenum drawMode = GL_TRIANGLES): drawMode(drawMode) {}
    void clear();
    void draw(const VertexArray& vao, const Buffer& ibo, const Shader& shader);

private:
    const GLenum drawMode;
};
