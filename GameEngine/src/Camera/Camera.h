#pragma once

#include "Graphics/ShaderClass/Shader.h"
#include "Input/Input.h"

class Camera
{
public:
	Camera();
	~Camera();

	void SetCoordUniforms(const Shader& shader);

	void Update();
	void ProcessMouseMovement(float xOffset, float yOffset);

	void SetModelMatrix(glm::mat4 model);
	glm::mat4 GetModelMatrix();

private:
	float m_cameraSpeed = 0.01f;

	float m_yaw;
	float m_pitch;

	//Camera Position / Target Vectors
	glm::vec3 m_position;
	glm::vec3 m_target;

	//World Vector
	glm::vec3 m_up;

	//Camera Local Vectors
	glm::vec3 m_direction;
	glm::vec3 m_camRight;
	glm::vec3 m_camUp;

	float m_FOV;

	glm::mat4 m_model = glm::mat4(1.0f);
	glm::mat4 m_view = glm::mat4(1.0f);
	glm::mat4 m_projection;
};