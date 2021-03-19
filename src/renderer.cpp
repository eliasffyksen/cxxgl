#include "renderer.hpp"

void Renderer::draw(const VertexArray& vao, const Buffer& ibo, const Shader& shader, GLenum mode)
{
    shader.bind();
    vao.bind();
    GLCall(glDrawElements(GL_LINES, ibo.getSize(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::clear()
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}