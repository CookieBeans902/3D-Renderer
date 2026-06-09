#pragma once
#include <string>

class Texture {
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	int m_Width;
	int m_Height;
	int m_Channels;
	unsigned int m_Format;
public:
	Texture(const std::string& filepath, unsigned int format);
	~Texture();

	void Bind() const;
	void Unbind() const;
};