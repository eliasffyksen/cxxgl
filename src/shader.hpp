
#pragma once

#include "log.hpp"
#include "error.hpp"

#include <GL/glew.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Shader
{
public:
    Shader();
    Shader(const std::string &filename);
    ~Shader();

    void read(const std::string &filename);
    void compile();
    void bind();
    void unbind();
    void setUniform4f(const std::string& name, float f0, float f1, float f2, float f3);

private:
    struct ShaderSource
    {
        enum class ShaderType
        {
            NONE = -1,
            VERTEX,
            FRAGMENT
        };

        ShaderSource() {}
        ShaderSource(const std::string &filename);

        std::stringstream sources[2];
    };

    ShaderSource shaderSource;
    GLuint programId = 0;

    GLuint compileShaderType(GLuint type, const std::string &source);
};
