
#pragma once

#include <GL/glew.h>
#include <vector>

#include "error.hpp"

template <class T>
class Buffer
{
public:
    Buffer(GLenum bufferType, std::vector<T> &data, GLenum usage = GL_STATIC_DRAW);
private:
    GLuint id;
};

template <class T>
Buffer<T>::Buffer(GLenum bufferType, std::vector<T> &data, GLenum usage)
{
    GLCall(glGenBuffers(1, &id));
    GLCall(glBindBuffer(bufferType, id));
    GLCall(glBufferData(bufferType, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW));
}
