
#include "vertexArray.hpp"

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &id));
    GLCall(glBindVertexArray(id));
}