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
#include "Texture.h"

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
       -0.5, -0.5, 0.0, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
       -0.5,  0.5, 0.0, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5,  0.5, 0.0, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5, -0.5, 0.0, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    VertexArray vao;

    VertexBuffer vbo(vertices, sizeof(vertices));

    IndexBuffer ibo(indices, 6);

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);
    vao.AddBuffer(vbo, layout);


    std::string shaderPath = projectRoot + "/res/shaders/basic.shader";


    Shader shader(shaderPath);

    shader.Bind();
    shader.SetUniform4f("u_Color", 1.0f, 0.5f, 0.2f, 1.0f);

    std::string texturePath1 = projectRoot + "/res/textures/container.jpg";
    std::string texturePath2 = projectRoot + "/res/textures/random.png";

    

    vao.Unbind();
    ibo.Unbind();
    shader.Unbind();

    GLCall(glActiveTexture(GL_TEXTURE0));
    Texture texture1(texturePath1, GL_RGB);
    GLCall(glActiveTexture(GL_TEXTURE1));
    Texture texture2(texturePath2, GL_RGBA);
    Renderer renderer;
    
    shader.Bind();
    shader.SetUniform1i("ourTexture1", 0);
    shader.SetUniform1i("ourTexture2", 1);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();

        float colorVal = (sin(glfwGetTime()) / 2.0f) + 0.5f;

        shader.Bind();
        shader.SetUniform4f("u_Color", 0.0f, colorVal, 0.0f, 1.0f);


        renderer.Draw(vao, ibo, shader);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    }
    glfwTerminate();
    return 0;
}