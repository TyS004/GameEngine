#include "gepch.h"

#include "Camera.h"

namespace GameEngine
{
	Camera::Camera()
	{
		//glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

		//Camera Position / Attributes
		m_FOV = 45.0f;

		//Camera Specific Matrix Math To Get Look At View Matrix(MATH TO FIND CAM UP, RIGHT, DIRECTION VECTORS)
		m_position = glm::vec3(0.0f, 0.0f, 3.0f);
		m_target = glm::vec3(0.0f, 0.0f, -1.0f);

		m_direction = glm::normalize(m_position - m_target);

		m_up = glm::vec3(0.0f, 1.0f, 0.0f);
		m_camRight = glm::normalize(glm::cross(m_up, m_direction));

		m_camUp = glm::cross(m_direction, m_camRight);

		//View, Projection Matricies
		m_view = glm::lookAt(m_position, m_target + m_position, m_up);
		m_projection = glm::perspective(glm::radians(m_FOV), 800.0f / 600.0f, 0.1f, 100.0f);

		m_yaw = -90.0f;
		m_pitch = 0.0f;
	}

	Camera::~Camera()
	{

	}

	void Camera::ProcessMouseMovement(float xOffset, float yOffset)
	{
		float sensitivity = 0.1f;

		m_yaw += xOffset * sensitivity;
		m_pitch -= yOffset * sensitivity;
	}

	void Camera::Update(Window window, float width, float height)
	{
		Move(window);

		//Updating Transformation Matricies
		m_direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		m_direction.y = sin(glm::radians(m_pitch));
		m_direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		m_target = glm::normalize(m_direction);

		m_view = glm::lookAt(m_position, m_target + m_position, m_up);
		m_projection = glm::perspective(glm::radians(m_FOV), width / height, 0.1f, 100.0f);

		//std::string msg = "Camera Position: " + std::to_string(m_position.x) + ", " + std::to_string(m_position.y) + ", " + std::to_string(m_position.z);
		//TRACE(msg);
	}

	void Camera::Move(Window window)
	{
		//Reset Camera Speed Every Frame
		m_cameraSpeed = 0.01f;

		if (KeyInput::isKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
		{
			m_cameraSpeed = 0.05f;
		}

		if (KeyInput::isKeyPressed(window, GLFW_KEY_W))
		{
			m_position += m_cameraSpeed * m_target;
		}

		if (KeyInput::isKeyPressed(window, GLFW_KEY_S))
		{
			m_position -= m_cameraSpeed * m_target;
		}

		if (KeyInput::isKeyPressed(window, GLFW_KEY_A))
		{
			m_position -= glm::normalize(glm::cross(m_target, m_camUp)) * m_cameraSpeed;
		}

		if (KeyInput::isKeyPressed(window, GLFW_KEY_D))
		{
			m_position += glm::normalize(glm::cross(m_target, m_camUp)) * m_cameraSpeed;
		}

		if (KeyInput::isKeyPressed(window, GLFW_KEY_SPACE))
		{
			m_position += m_up * m_cameraSpeed;
		}

		if (KeyInput::isKeyPressed(window, GLFW_KEY_LEFT_CONTROL))
		{
			m_position += -m_up * m_cameraSpeed;
		}
	}

	glm::mat4 Camera::GetViewMatrix()
	{
		return m_view;
	}

	glm::mat4 Camera::GetProjectionMatrix()
	{
		return m_projection;
	}
}
