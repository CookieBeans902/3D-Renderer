#pragma once

#include <string>
struct ShaderProgramSource {
	std::string vertexShader;
	std::string fragmentShader;
};

class Shader
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;

public:
	Shader(const std::string& filepath);
	~Shader();
	ShaderProgramSource ParseShader();
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	// Uniform declarations
	void SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4);
	void SetUniform1i(const std::string& name, int value);
	int GetUniformLocation(const std::string& name);
	void Bind() const;
	void Unbind() const;
};