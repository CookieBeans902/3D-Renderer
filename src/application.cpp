#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>

#include "renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "VertexArray.h"
#include "VertexBufferLayout.h"

#include "Shader.h"

#ifndef ROOT_DIR
#define ROOT_DIR = "."
#endif ROOT_DIR

int main(void)
{
   {
    std::string projectRoot = ROOT_DIR;
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        return -1;
    }

    float vertices[] = {
       -0.5, -0.5,
        0.5, -0.5,
        0.5,  0.5,
       -0.5,  0.5
    };

    unsigned int indices[]{
        0, 1 ,2,
        2, 3, 0
    };

    VertexArray vao;

    VertexBuffer vbo(vertices, sizeof(vertices));

    IndexBuffer ibo(indices, 6);

    VertexBufferLayout layout;
    layout.Push<float>(2);
    vao.AddBuffer(vbo, layout);


    std::string shaderPath = projectRoot + "/res/shaders/basic.shader";


    Shader shader(shaderPath);

    shader.Bind();
    shader.SetUniform4f("u_Color", 1.0f, 0.5f, 0.2f, 1.0f);

    vao.Unbind();
    ibo.Unbind();
    shader.Unbind();
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT); 

        vao.Bind();
        ibo.Bind();
        shader.Bind();
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    }
    glfwTerminate();
    return 0;
}