#pragma once

#include "gepch.h"

class VBO
{
public:
	inline VBO(float* vertices, uint32_t size)
	{
		glGenBuffers(1, &m_ID); 

		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	inline void Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_ID); }
	inline void Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
	inline void Delete() { glDeleteBuffers(1, &m_ID); }

private:
	uint32_t m_ID;
};
