
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

void VertexArray::addBuffer(Buffer& vertexBuffer, VertexBufferLayout& vbl)
{
    vertexBuffer.bind();
    size_t offset = 0;

    for (size_t i = 0; i < vbl.attribs.size(); i++) {
        VertexArrayAttrib& e = vbl.attribs[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, e.count, e.type, e.normalized, vbl.stride, (const void*) offset));
        offset += e.count * e.getTypeSize();
    }
}
