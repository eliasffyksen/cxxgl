
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "log.hpp"
#include "error.hpp"

class Window
{
public:
    Window(int width, int height, const char* title, std::vector<std::pair<int, int>> windowHints);

    int shouldClose(void);
    void swapBuffers(void);
    void pollEvents(void);

    GLFWwindow * glfwWindow;
};