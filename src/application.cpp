#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>

//#define Stringify(x) #x
//#define TO_STRING(x) Stringify(x)
struct ShaderProgramSource {
    std::string vertexShader;
    std::string fragmentShader;
};
static ShaderProgramSource ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);
    std::string line;
    std::stringstream ss[2];
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.length() == 0) {
            continue;
        }
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                std::cout << "Ran" << std::endl;    
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            if (type != ShaderType::NONE) {
                ss[(int)type] << line << "\n";
            }
        }
    }
    return { ss[0].str(),ss[1].str() };
}
static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    // TODO: Error handling
    int result = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) 
    {
        int length = 1;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile" << ((type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment") << "Shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0; 
    }   

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) 
{
    unsigned int program = glCreateProgram();

    unsigned int vs = CompileShader(GL_VERTEX_SHADER,vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER,fragmentShader);

    glAttachShader(program,vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    
    return program;
}

int main(void)
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

    float positions[] = {
       -0.5, -0.5,
        0.5, -0.5,
        0.5,  0.5,
       -0.5,  0.5
    };

    unsigned int indices[]{
        0, 1 ,2,
        2, 3, 0
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER,buffer);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    
    std::string shaderPath = projectRoot + "/res/shaders/basic.shader";
    std::cout << shaderPath << std::endl;
    ShaderProgramSource source = ParseShader(shaderPath);


    std::cout << "VERTEX" << std::endl;
    std::cout << source.vertexShader << std::endl;
    std::cout << "FRAGMENT" << std::endl;
    std::cout << source.fragmentShader << std::endl;

    unsigned int shader = CreateShader(source.vertexShader, source.fragmentShader);
    glUseProgram(shader);

    int location = glGetUniformLocation(shader, "u_Color");
    std::cout << location << std::endl;
        glUniform4f(location, 1.0f, 0.0f, 0.0f, 1.0f);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT,nullptr);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}