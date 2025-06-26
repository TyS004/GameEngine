#pragma once

#include <glad/glad.h>

class VBO
{
public:
	GLuint ID;
	inline VBO()
	{
		ID = 0;
	}
	inline VBO(GLfloat* vertices, int size)
	{
		glGenBuffers(1, &ID); 
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	inline void Bind() { glBindBuffer(GL_ARRAY_BUFFER, ID); }
	inline void Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
	inline void Delete() { glDeleteBuffers(1, &ID); }
};
