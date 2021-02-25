#pragma once

#include <GL/glew.h>
#include <vector>

#include "error.hpp"

struct VertexArrayAttrib
{
    GLenum type;
    uint32_t count;
    GLboolean normalized;

    uint32_t getTypeSize();
};

class VertexBufferLayout
{
public:
    std::vector<VertexArrayAttrib> attribs;
    uint32_t stride = 0;

    template<typename T>
    void addAttrib(uint32_t count) { FATAL_ERR("Invalid attribute type"); }

    template<>
    void addAttrib<float>(uint32_t count)
    {
        attribs.push_back({ GL_FLOAT, count, false});
        stride += count * sizeof(float);
    }

    template<>
    void addAttrib<uint32_t>(uint32_t count)
    {
        attribs.push_back({ GL_FLOAT, count, false});
        stride += count * sizeof(float);
    }

    template<>
    void addAttrib<uint8_t>(uint32_t count)
    {
        attribs.push_back({ GL_UNSIGNED_BYTE, count, false});
        stride += count * sizeof(u_char);
    }
};
