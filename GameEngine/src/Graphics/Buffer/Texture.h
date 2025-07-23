#pragma once

#include "gepch.h"

namespace GameEngine
{
	class GE_API Texture
	{
	public:
		inline Texture(uint32_t width, uint32_t height)
		{
			m_pixelData = nullptr;
			m_width = width;
			m_height = height;
			m_numChannels = 0;

			glGenTextures(1, &m_ID);
			std::cout << "Generated texture ID: " << m_ID << ", size: " << m_width << "x" << m_height << std::endl;
			glBindTexture(GL_TEXTURE_2D, m_ID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

			//Texture Settings
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glBindTexture(GL_TEXTURE_2D, 0);
		}

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

		inline void Bind() const { glBindTexture(GL_TEXTURE_2D, m_ID); }
		inline void Unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }
		inline void Delete() const { glDeleteTextures(1, &m_ID); }

		inline uint32_t getID() const { return m_ID; }

	private:
		uint32_t m_ID;
		unsigned char* m_pixelData;

		int m_width, m_height, m_numChannels;
	};
}
