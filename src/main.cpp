
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "log.hpp"
#include "shader.hpp"
#include "error.hpp"
#include "window.hpp"
#include "vertexArray.hpp"
#include "buffer.hpp"
#include "renderer.hpp"

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

    float positions[] = {
        -0.5f, 0.5f,  // TR
        0.5f, 0.5f,   // TL
        -0.5f, -0.5f, // BR
        0.5f, -0.5f,  // BL
    };

    unsigned int indices[] = { 0, 1, 2, 1, 3, 2, };

    VertexArray vao;

    Buffer vertexBuffer(positions, sizeof(positions));

    VertexBufferLayout vbl;
    vbl.addAttrib<float>(2);

    vao.addBuffer(vertexBuffer, vbl);

    Buffer ibo(indices, sizeof(indices), GL_ELEMENT_ARRAY_BUFFER);

    Shader shader("./res/shaders/basic.glsl");
    shader.compile();

    LOG("Running game loop");
    float r = 0;

    Renderer renderer;

    /* Loop until the user closes the window */
    while (!window.shouldClose())
    {
        /* Render here */
        shader.bind();
        shader.setUniform4f("u_Color", r, 0.2f, 0.3f, 1.0f);
        r += 0.01f;
        if (r > 1.0f)
            r = 0.0f;

        renderer.clear();
        renderer.draw(vao, ibo, shader);

        window.swapBuffers();
        window.pollEvents();
    }

    LOG("Terminating");

    glfwTerminate();
    return 0;
}