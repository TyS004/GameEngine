#pragma once

#include "gepch.h"

#include "Texture.h" 

namespace GameEngine
{
	class GE_API FBO
	{
	public:
		inline FBO(const Texture& texture)
		{
			glGenFramebuffers(1, &m_ID);
			glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

			m_texture = &texture;
			m_width = texture.GetWidth();
			m_height = texture.GetHeight();

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.GetID(), 0);
			glDrawBuffer(GL_COLOR_ATTACHMENT0);

			glViewport(0, 0, m_width, m_height);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		inline uint32_t GetID() const { return m_ID; }

		inline int GetWidth() const { return m_width; }
		inline int GetHeight() const { return m_height; }

		inline void Bind() const { glBindFramebuffer(GL_FRAMEBUFFER, m_ID); }
		inline void Unbind() const { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
		inline void Delete() const { glDeleteFramebuffers(1, &m_ID); }
		inline void Debug()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

			INFO("Checking FBO:");
			INFO("FBO ID: " + std::to_string(m_ID));
			INFO("Texture ID: " + std::to_string(m_texture->GetID()));
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
}