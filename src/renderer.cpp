#include "renderer.hpp"

void Renderer::draw(const VertexArray& vao, const Buffer& ibo, const Shader& shader)
{
    shader.bind();
    vao.bind();
    GLCall(glDrawElements(drawMode, ibo.getSize(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::clear()
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}