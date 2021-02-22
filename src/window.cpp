
#include "window.hpp"

Window::Window(int width, int height, const char* title, std::vector<std::pair<int, int>> windowHints)
{
    /* Initialize the library */
    if (!glfwInit())
        FATAL_ERR("Failed to init glfw");

    for (auto h: windowHints) {
        glfwWindowHint(h.first, h.second);
    }

    glfwWindow = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!glfwWindow)
    {
        glfwTerminate();
        FATAL_ERR("Failed to create window");
    }

    glfwMakeContextCurrent(glfwWindow);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        FATAL_ERR("Failed to initialize GLEW");
}

int Window::shouldClose(void)
{
    return glfwWindowShouldClose(glfwWindow);
}

void Window::swapBuffers(void)
{
    GLCall(glfwSwapBuffers(glfwWindow));
}

void Window::pollEvents(void)
{
    GLCall(glfwPollEvents());
}