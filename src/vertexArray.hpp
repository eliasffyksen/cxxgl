#pragma once

#include <vector>
#include <GL/glew.h>

#include "error.hpp"
#include "buffer.hpp"

struct VertexArrayAttrib
{
public:
    GLenum type;
    uint count;
    GLboolean normalized;

    uint getTypeSize();
};

class VertexBufferLayout
{
public:
    std::vector<VertexArrayAttrib> attribs;
    uint stride = 0;

    template<typename T>
    void addAttrib(uint count) { FATAL_ERR("Invalid attribute type"); }

    template<>
    void addAttrib<float>(uint count)
    {
        attribs.push_back({ GL_FLOAT, count, false});
        stride += count * sizeof(float);
    }

    template<>
    void addAttrib<uint>(uint count)
    {
        attribs.push_back({ GL_FLOAT, count, false});
        stride += count * sizeof(float);
    }

    template<>
    void addAttrib<u_char>(uint count)
    {
        attribs.push_back({ GL_UNSIGNED_BYTE, count, false});
        stride += count * sizeof(u_char);
    }
};

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void bind();
    void unbind();

    void addBuffer(Buffer& vertexBuffer, VertexBufferLayout& vbl);

private:
    GLuint id;
};