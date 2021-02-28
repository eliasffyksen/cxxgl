
#include "buffer.hpp"

Buffer::Buffer(const void *data, size_t size, GLenum bufferType, GLenum usage) : bufferType(bufferType)
{
    GLCall(glGenBuffers(1, &id));
    GLCall(glBindBuffer(bufferType, id));
    GLCall(glBufferData(bufferType, size, data, usage));
    bufferSize = size;
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &id);
}

void Buffer::bind() const
{
    GLCall(glBindBuffer(bufferType, id));
}

void Buffer::unbind() const
{
    GLCall(glBindBuffer(bufferType, 0));
}

GLuint Buffer::getId() const
{
    return id;
}

size_t Buffer::getSize() const
{
    return bufferSize;
}
