#pragma once

#include "Graphics/Window/Window.h"

class KeyInput
{
public:
	static bool isKeyPressed(int keycode);
	static bool isKeyReleased(int keycode);
};

class MouseInput
{
public:
	static bool isMouseButtonPressed(int button);
	void getMousePos(double& x, double& y);
};