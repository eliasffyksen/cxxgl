
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "log.hpp"
#include "shader.hpp"
#include "error.hpp"
#include "window.hpp"
#include "vertexArray.hpp"
#include "buffer.hpp"

int main(void)
{
    Window window(800, 400, "cherno-opengl",
                  {
                      {GLFW_CONTEXT_VERSION_MAJOR, 4},
                      {GLFW_CONTEXT_VERSION_MINOR, 6},
                      {GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE},
                      {GLFW_RESIZABLE, GLFW_FALSE},
                  });

    LOG("Window created, GLEW initialized");
    LOG("Using OpenGL version: " << glGetString(GL_VERSION));

    std::vector<float> positions = {
        -0.5f, 0.5f,  // TR
        0.5f, 0.5f,   // TL
        -0.5f, -0.5f, // BR
        0.5f, -0.5f,  // BL
    };

    std::vector<unsigned int> indices = { 0, 1, 2, 1, 3, 2, };

    VertexArray vao;

    Buffer<float> buffer(GL_ARRAY_BUFFER, positions);

    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));

    Buffer<unsigned int> ibo(GL_ELEMENT_ARRAY_BUFFER, indices);

    GLuint shader = createShader(ShaderSource("./res/shaders/basic.glsl"));
    GLCall(glUseProgram(shader));

    GLCall(GLint u_Color = glGetUniformLocation(shader, "u_Color"));
    if (u_Color == -1)
        FATAL_ERR("Invalid uniform location");

    GLCall(glUniform4f(u_Color, 0.1f, 0.2f, 0.3f, 1.0f));

    LOG("Running game loop");

    /* Loop until the user closes the window */
    while (!window.shouldClose())
    {
        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        GLCall(glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, nullptr));
        window.swapBuffers();
        window.pollEvents();
    }

    GLCall(glDeleteProgram(shader));

    LOG("Terminating");

    glfwTerminate();
    return 0;
}