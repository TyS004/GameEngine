#include "gepch.h"

#include "Input.h"

static GLFWwindow* m_Window = Window::getWindow();


bool KeyInput::isKeyPressed(int keycode)
{
	if (glfwGetKey(Window::getWindow(), keycode) == GLFW_PRESS)
	{
		return true;
	}
	return false;
}

bool KeyInput::isKeyReleased(int keycode)
{
	if (glfwGetKey(Window::getWindow(), keycode) == GLFW_RELEASE)
	{
		return true;
	}
	return false;
}

//Init Last Mouse to Center of Screen
std::pair<float, float> MouseInput::lastMousePos = std::pair<float, float>(Window::GetWidth() / 2, Window::GetHeight() / 2);

bool MouseInput::isMouseButtonPressed(int button)
{
	if (glfwGetMouseButton(Window::getWindow(), button) == GLFW_PRESS)
	{
		return true;
	}
	return false;
}

std::pair<float, float> MouseInput::getMousePos()
{
	double x, y;

	glfwGetCursorPos(Window::getWindow(), &x, &y);

	return std::pair<float, float>(x, y);
}
