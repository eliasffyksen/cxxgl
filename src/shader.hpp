
#pragma once

#include "log.hpp"
#include "error.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

class Shader
{
public:
    Shader();
    Shader(const std::string &filename);
    ~Shader();

    void load(const std::string &filename);
    void compile();
    void bind() const;
    void unbind() const;

    void setUniform1i(const std::string& name, int i);
    void setUniform4f(const std::string& name, float f0, float f1, float f2, float f3);

    void setUniformMatrix4f(const std::string& name, const glm::mat4& u_mat4);

    GLint getUniformLocation(const std::string& name);

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
    std::unordered_map<std::string, GLint> locationCache;

    GLuint compileShaderType(GLuint type, const std::string &source);
};
