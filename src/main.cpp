
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
    GLCall(glEnable(GL_BLEND));

    float positions[] = {
        -0.5f,  0.5f,  0.0f,  1.0f, // TL
         0.5f,  0.5f,  1.0f,  1.0f, // TR
        -0.5f, -0.5f,  0.0f,  0.0f, // BL
         0.5f, -0.5f,  1.0f,  0.0f, // BR
    };

    unsigned int indices[] = { 0, 1, 2, 1, 3, 2, };

    VertexArray vao;

    Buffer vertexBuffer(positions, sizeof(positions));

    VertexBufferLayout vbl;
    vbl.addAttrib<float>(2);
    vbl.addAttrib<float>(2);

    vao.addBuffer(vertexBuffer, vbl);

    Buffer ibo(indices, sizeof(indices), GL_ELEMENT_ARRAY_BUFFER);

    glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.f, 1.f, -1.0f, 1.0f);
    
    Shader shader("./res/shaders/basic.glsl");
    shader.compile();
    shader.bind();
    shader.setUniformMatrix4f("u_MVP", proj);

    Texture opengl("./res/textures/OpenGL.png");
    opengl.bind();
    shader.setUniform1i("u_Tex", 0);

    LOG("Running game loop");

    Renderer renderer;

    /* Loop until the user closes the window */
    while (!window.shouldClose())
    {
        /* Render here */
        shader.bind();

        renderer.clear();
        renderer.draw(vao, ibo, shader);

        window.swapBuffers();
        window.pollEvents();
    }

    LOG("Terminating");

    glfwTerminate();
    return 0;
}