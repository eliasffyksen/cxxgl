
#pragma once

#include "log.hpp"
#include "error.hpp"

#include <GL/glew.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

struct ShaderSource {
    enum class ShaderType {
        NONE = -1, VERTEX, FRAGMENT
    };

    ShaderSource() {}
    ShaderSource(const std::string& filename);

    std::stringstream sources[2];
};

void readShader(const std::string& filename, ShaderSource& shaderSource);

GLuint compileShader(GLuint type, const std::string& source);
GLuint createShader(const ShaderSource& source);
