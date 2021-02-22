
#pragma once

#include <GL/glew.h>

#include "log.hpp"

#define GLCall(x) {\
    GLClearError();\
    x;\
    GLPrintError();\
}

void GLPrintError();
void GLClearError();
