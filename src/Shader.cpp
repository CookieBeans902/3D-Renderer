#include "Shader.h"
#include "renderer.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>
Shader::Shader(std::string vertexPath, std::string fragmentPath)
:m_VertexShaderPath(std::move(vertexPath)), m_FragmentShaderPath(std::move(fragmentPath))
{
    ShaderProgramSource source = ParseShader();
    m_RendererID = CreateShader(source.vertexShader, source.fragmentShader);
}
Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}
ShaderProgramSource Shader::ParseShader()
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vsFile(m_VertexShaderPath);
    std::ifstream fsFile(m_FragmentShaderPath);

    try
    {
        vsFile.open(m_VertexShaderPath);
        fsFile.open(m_FragmentShaderPath);

        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vsFile.rdbuf();
        fShaderStream << fsFile.rdbuf();

        vsFile.close();
        fsFile.close();
        
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    return { vertexCode , fragmentCode };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));
    int result = 0;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length = 1;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile" << ((type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment") << "Shader!" << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }
    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    GLCall(unsigned int program = glCreateProgram());

    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));

    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

void Shader::SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4)
{
    GLCall(glUniform4f(GetUniformLocation(name), v1, v2, v3, v4));
}
void Shader::SetUniform3f(const std::string& name, float v1, float v2, float v3)
{
    GLCall(glUniform3f(GetUniformLocation(name), v1, v2, v3));
}
void Shader::SetUniform3f(const std::string& name, glm::vec3 pos)
{
    GLCall(glUniform3f(GetUniformLocation(name), pos.x, pos.y, pos.z));
}
void Shader::SetUniform1i(const std::string& name, int value)
{
    GLCall(glUniform1i(GetUniformLocation(name),value));
}
void Shader::SetUniformMatrix4fv(const std::string& name, glm::mat4 matrix)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix)));
}

int Shader::GetUniformLocation(const std::string& name)
{
    GLCall(int location = glGetUniformLocation(m_RendererID,name.c_str()));
    if (location == -1) {
        std::cout << "Location of '" << name << "' uniform is missing. Please refer. " << std::endl;
    }
    return location;
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}
