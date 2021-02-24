
#include "vertexArray.hpp"

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &id));
    bind();
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &id));
}

void VertexArray::bind()
{
    GLCall(glBindVertexArray(id));
}

void VertexArray::unbind()
{
    GLCall(glBindVertexArray(0));
}