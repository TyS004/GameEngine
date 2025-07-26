#pragma once

#include "gepch.h"

namespace GameEngine
{
	class GE_API RBO
	{
	public:
		inline RBO(const FBO& FBO1)
		{
			FBO1.Bind();
			glGenRenderbuffers(1, &m_ID);
			glBindRenderbuffer(GL_RENDERBUFFER, m_ID);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, FBO1.GetWidth(), FBO1.GetHeight());
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_ID);
			FBO1.Unbind();
		}
	private:
		uint32_t m_ID;
	};
}