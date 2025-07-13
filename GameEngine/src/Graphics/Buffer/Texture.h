#pragma once

#include "gepch.h"

class Texture
{
public:
	inline Texture(const char* filename)
	{
		m_pixelData = stbi_load(filename, &m_width, &m_height, &m_numChannels, 0);

		GLenum format = (m_numChannels == 4) ? GL_RGBA : GL_RGB;

		glGenTextures(1, &m_ID);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_ID);

		//Texture Settings
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		//Attach File to Texture Buffer Object
		glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, m_pixelData);
		stbi_image_free(m_pixelData);
		
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	inline void Bind() { glBindTexture(GL_TEXTURE_2D, m_ID); }
	inline void Unbind() { glBindTexture(GL_TEXTURE_2D, 0); }
	inline void Delete() { glDeleteTextures(1, &m_ID); }

private:
	uint32_t m_ID;
	unsigned char* m_pixelData;

	int m_width, m_height, m_numChannels;
};
