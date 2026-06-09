#include "Texture.h"
#include "renderer.h"
#include <iostream>
#include "external/stb_image.h"

Texture::Texture(const std::string& filepath, unsigned int format)
	:m_FilePath(filepath), m_Width(0), m_Height(0), m_Channels(3), m_Format(format)
{
	stbi_set_flip_vertically_on_load(true);
	GLCall(glGenTextures(1, &m_RendererID));
	unsigned char* data = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_Channels,0);
	Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (!data) {
		std::cout << "Failed to load texture [" << m_FilePath << "] " << std::endl;
		stbi_image_free(data);
		return;
	}
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, m_Format, m_Width, m_Height, 0, m_Format, GL_UNSIGNED_BYTE, data));
	GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	stbi_image_free(data);
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}
void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
