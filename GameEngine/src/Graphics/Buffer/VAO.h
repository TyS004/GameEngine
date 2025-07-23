#pragma once

#include "gepch.h"

#include "VBO.h"

namespace GameEngine
{
	class GE_API VAO
	{
	public:
		inline VAO()
		{
			glGenVertexArrays(1, &m_ID);
		}

		inline void LinkAttribute(const VBO& VBO1, uint32_t layout, uint32_t count, uint32_t type, uint32_t stride, uint32_t offset)
		{
			VBO1.Bind();
			glVertexAttribPointer(layout, count, type, GL_FALSE, stride, (const void*)offset);
			glEnableVertexAttribArray(layout);
			VBO1.Unbind();
		}

		inline void Bind() const { glBindVertexArray(m_ID); }
		inline void Unbind() const { glBindVertexArray(0); }
		inline void Delete() const { glDeleteVertexArrays(1, &m_ID); }

	private:
		uint32_t m_ID;
	};
}