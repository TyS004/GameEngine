#include "gepch.h"

#include "Object.h"

static int ID = 0;

Object::Object(float x, float y, float z)
	: position(glm::vec3(x, y, z))
{
	m_ID = ID++;

	m_VAO = std::make_unique<VAO>();
	m_VBO = std::make_unique<VBO>(m_buffer, sizeof(m_buffer));
	
	//Set Attributes
	m_VAO->Bind();
	m_VBO->Bind();

	m_VAO->LinkAttribute(*m_VBO, 0, 3, GL_FLOAT, 8 * sizeof(float), 0);
	m_VAO->LinkAttribute(*m_VBO, 1, 3, GL_FLOAT, 8 * sizeof(float), 3 * sizeof(float));
	m_VAO->LinkAttribute(*m_VBO, 2, 2, GL_FLOAT, 8 * sizeof(float), 6 * sizeof(float));
	
	m_VAO->Unbind();
	m_VBO->Unbind();

	m_model = glm::translate(m_model, position);
}

void Object::Draw() const
{
	m_VAO->Bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	m_VAO->Unbind();
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