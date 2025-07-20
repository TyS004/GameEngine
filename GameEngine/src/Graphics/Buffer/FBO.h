#pragma once

#include "gepch.h"

#include "Texture.h" 

class FBO
{
public:
	inline FBO(const Texture& texture, uint32_t width, uint32_t height)
	{
		glGenFramebuffers(1, &m_ID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

		m_texture = &texture;
		m_width = width;
		m_height = height;

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.getID(), 0);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);

		glViewport(0, 0, width, height);
		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	inline uint32_t getID() const { return m_ID; }

	inline void Bind() const { glBindFramebuffer(GL_FRAMEBUFFER, m_ID); }
	inline void Unbind() const { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
	inline void Delete() const { glDeleteFramebuffers(1, &m_ID); }
	inline void Debug() 
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

		INFO("Checking FBO:");
		INFO("FBO ID: " + std::to_string(m_ID));
		INFO("Texture ID: " + std::to_string(m_texture->getID()));
		INFO("Window size: " + std::to_string(m_width) + "x" + std::to_string(m_height));

		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

		if (status != GL_FRAMEBUFFER_COMPLETE) {
			WARN("Framebuffer error: ");
			switch (status) {
			case GL_FRAMEBUFFER_UNDEFINED: WARN("UNDEFINED"); break;
			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT: WARN("INCOMPLETE_ATTACHMENT"); break;
			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: WARN("MISSING_ATTACHMENT"); break;
			case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER: WARN("INCOMPLETE_DRAW_BUFFER"); break;
			case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER: WARN("INCOMPLETE_READ_BUFFER"); break;
			case GL_FRAMEBUFFER_UNSUPPORTED: WARN("UNSUPPORTED"); break;
			default: WARN("UNKNOWN ERROR"); break;
			}
		}
		else
		{
			INFO("Framebuffer is COMPLETE");
		}
	}
private:
	uint32_t m_ID;
	const Texture* m_texture;

	uint32_t m_width, m_height;
};
