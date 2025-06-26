#pragma once
#pragma once

#include <glad/glad.h>

class EBO
{
public:
	GLuint ID;
	inline EBO(GLfloat* vertices, int size)
	{
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	inline void Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); }
	inline void Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
	inline void Delete() { glDeleteBuffers(1, &ID); }
};