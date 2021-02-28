
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "log.hpp"
#include "shader.hpp"
#include "error.hpp"
#include "window.hpp"
#include "vertexArray.hpp"
#include "buffer.hpp"
#include "renderer.hpp"
#include "texture.hpp"

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

    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    float positions[] = {
        -0.5f,  0.5f,  1.0f,  1.0f, // FTL
         0.5f,  0.5f,  1.0f,  1.0f, // FTR
        -0.5f, -0.5f,  1.0f,  1.0f, // FBL
         0.5f, -0.5f,  1.0f,  1.0f, // FBR
        -0.5f,  0.5f,  2.0f,  1.0f, // BTL
         0.5f,  0.5f,  2.0f,  1.0f, // BTR
        -0.5f, -0.5f,  2.0f,  1.0f, // BBL
         0.5f, -0.5f,  2.0f,  1.0f, // BBR
    };

    unsigned int indices[] = {
        0, 1,
        1, 3,
        3, 2,
        0, 2,
        4, 5,
        5, 7,
        7, 6,
        4, 6,
        0, 4,
        1, 5,
        2, 6,
        3, 7
    };

    VertexArray vao;

    Buffer vertexBuffer(positions, sizeof(positions));

    VertexBufferLayout vbl;
    vbl.addAttrib<float>(4);
    // vbl.addAttrib<float>(2);

    vao.addBuffer(vertexBuffer, vbl);

    Buffer ibo(indices, sizeof(indices), GL_ELEMENT_ARRAY_BUFFER);

    Shader shader("./res/shaders/basic.glsl");
    shader.compile();
    shader.bind();

    Texture opengl("./res/textures/OpenGL.png");
    opengl.bind();
    // shader.setUniform1i("u_Tex", 0);

    LOG("Running game loop");

    Renderer renderer;
    float r = 0.0f;

    /* Loop until the user closes the window */
    while (!window.shouldClose())
    {
        /* Render here */
        shader.bind();
        shader.setUniform1f("r", r);
        r += 0.01f;

        renderer.clear();
        renderer.draw(vao, ibo, shader);

        window.swapBuffers();
        window.pollEvents();
    }

    LOG("Terminating");

    glfwTerminate();
    return 0;
}