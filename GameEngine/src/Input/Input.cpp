#include "gepch.h"

#include "Input.h"

bool KeyInput::isKeyPressed(Window window, int keycode)
{
	if (glfwGetKey(window.getWindow(), keycode) == GLFW_PRESS)
	{
		return true;
	}
	return false;
}

bool KeyInput::isKeyReleased(Window window, int keycode)
{
	if (glfwGetKey(window.getWindow(), keycode) == GLFW_RELEASE)
	{
		return true;
	}
	return false;
}

bool MouseInput::isMouseButtonPressed(Window window, int button)
{
	if (glfwGetMouseButton(window.getWindow(), button) == GLFW_PRESS)
	{
		return true;
	}
	return false;
}

std::pair<float, float> MouseInput::getMousePos(Window window)
{
	double x, y;

	glfwGetCursorPos(window.getWindow(), &x, &y);

	return std::pair<float, float>(x, y);
}
