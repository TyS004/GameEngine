#pragma once

#include "gepch.h"

class RBO
{
public:
	inline RBO(const FBO& FBO1, uint32_t width, uint32_t height)
	{
		FBO1.Bind();
		glGenRenderbuffers(1, &m_ID);
		glBindRenderbuffer(GL_RENDERBUFFER, m_ID);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_ID);
		FBO1.Unbind();
	}
private:
	uint32_t m_ID;
};