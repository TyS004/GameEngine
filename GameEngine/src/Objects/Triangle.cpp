#include "gepch.h"
#include "Triangle.h"

#include "Graphics/VBO.h"
#include "Graphics/VAO.h"
#include "Graphics/EBO.h"

#include "Graphics/ShaderClass/Shader.h"


Triangle::Triangle(float x, float y, float z)
	: position(glm::vec3(x, y, z))
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
	m_model = glm::translate(m_model, position);
}

void Triangle::Draw() const
{
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Triangle::Transform(float x, float y, float z, const Shader& shader)
{
	position.x = x;
	position.y = y;
	position.z = z;

	//m_model = glm::translate(m_model, position);

	shader.setUniformVar(m_model, "model");
}

void Triangle::setUniform(const Shader& shader)
{
	shader.setUniformVar(m_model, "model");
}