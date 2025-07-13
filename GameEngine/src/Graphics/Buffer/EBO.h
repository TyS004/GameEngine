#pragma once

#include "gepch.h"

class EBO
{
public:
	inline EBO(uint32_t* vertices, int size)
	{
		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	inline void Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID); }
	inline void Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
	inline void Delete() { glDeleteBuffers(1, &m_ID); }

private:
	uint32_t m_ID;
};