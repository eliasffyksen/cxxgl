
#pragma once

#include <GL/glew.h>

#include "log.hpp"

#define GLCall(x) \
    GLClearError();\
    x;\
    BREAK_IF(!GLPrintError(#x, __FILE__, __LINE__))

bool GLPrintError(const char* funct, const char* file, int line);
void GLClearError();
