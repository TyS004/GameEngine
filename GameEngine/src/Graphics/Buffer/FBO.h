#pragma once

#include "gepch.h"

class FBO
{
public:
	inline FBO(float* vertices, uint32_t size)
	{
		glGenFramebuffers(1, &m_ID);
		glBindBuffer(GL_FRAMEBUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	inline void Bind() { glBindBuffer(GL_ARRAY_BUFFER, m_ID); }
	inline void Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
	inline void Delete() { glDeleteBuffers(1, &m_ID); }

private:
	uint32_t m_ID;
};
