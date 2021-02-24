
#include "buffer.hpp"

Buffer::Buffer(const void *data, size_t size, GLenum bufferType, GLenum usage) : bufferType(bufferType)
{
    GLCall(glGenBuffers(1, &id));
    GLCall(glBindBuffer(bufferType, id));
    GLCall(glBufferData(bufferType, size, data, usage));
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &id);
}

void Buffer::bind()
{
    GLCall(glBindBuffer(bufferType, id));
}

void Buffer::unbind()
{
    GLCall(glBindBuffer(bufferType, 0));
}

GLuint Buffer::getId()
{
    return id;
}
