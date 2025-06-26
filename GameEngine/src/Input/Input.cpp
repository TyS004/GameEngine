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



bool MouseInput::isMouseButtonPressed(int button)
{
	if (glfwGetMouseButton(Window::getWindow(), button) == GLFW_PRESS)
	{
		return true;
	}
	return false;
}

void MouseInput::getMousePos(double& x, double& y)
{
	glfwGetCursorPos(m_Window, &x, &y);
}