#pragma once

#include "gepch.h"

#include "VBO.h"

class VAO
{
public:
	GLuint ID;
	inline VAO() { glGenVertexArrays(1, &ID); }

	inline void LinkAttribute(VBO VBO1, GLuint layout, unsigned int count, GLuint type, int stride, int offset) 
	{
		VBO1.Bind();
		glVertexAttribPointer(layout, count, type, GL_FALSE, stride, (const void*)offset);
		glEnableVertexAttribArray(layout);
		VBO1.Unbind();
	}
	inline void Bind() { glBindVertexArray(ID); }
	inline void Unbind() { glBindVertexArray(0); }
	inline void Delete() { glDeleteVertexArrays(1, &ID); }
};
