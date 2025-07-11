#include "gepch.h"
#include "Object.h"

#include "Graphics/Buffer/VBO.h"
#include "Graphics/Buffer/VAO.h"
#include "Graphics/Buffer/EBO.h"

#include "Graphics/ShaderClass/Shader.h"

static int ID = 0;

Object::Object(float x, float y, float z)
	: position(glm::vec3(x, y, z))
{
	m_ID = ID++;

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

void Object::Draw() const
{
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Object::Translate(float x, float y, float z, const Shader& shader)
{
	float prev_X = position.x;
	float prev_Y = position.y;
	float prev_Z = position.z;

	position.x = x;
	position.y = y;
	position.z = z;

	m_model = glm::translate(m_model, glm::vec3(position.x - prev_X, position.y - prev_Y, position.z - prev_Z));
}

void Object::setUniform(const Shader& shader)
{
	shader.setUniformVar(m_model, "model");
}

int Object::getID()
{
	return m_ID;
}

glm::vec3 Object::getTransform() const
{
	return position;
}