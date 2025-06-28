#include "gepch.h"
#include "Triangle.h"

#include "Graphics/VBO.h"
#include "Graphics/VAO.h"
#include "Graphics/EBO.h"

#include "Graphics/ShaderClass/Shader.h"


Triangle::Triangle(int bufferSize)
	: m_bufferSize(bufferSize)
{
	VAO VAO1;
	VBO VBO1(m_buffer, sizeof(m_buffer));
	EBO EBO1(m_indices, sizeof(m_indices));

	//Bind Array Vertex
	VAO1.Bind();
	//EBO1.Bind();

	//Set Attributes
	VAO1.LinkAttribute(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), 0);
	VAO1.LinkAttribute(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), 3 * sizeof(float));
}

void Triangle::Draw() const
{
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Triangle::Rotate(Camera& camera, float rotation) const
{
	camera.SetModelMatrix(glm::rotate(camera.GetModelMatrix(), rotation, glm::vec3(0.0f, 1.0f, 0.0f)));
}