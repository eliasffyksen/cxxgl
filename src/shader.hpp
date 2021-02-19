
#pragma once

#include "log.hpp"

#include <GL/glew.h>
#include <iostream>

GLuint compileShader(GLuint type, const std::string& source);
GLuint createShader(const std::string& vertexShader, const std::string& fragmentShader);
