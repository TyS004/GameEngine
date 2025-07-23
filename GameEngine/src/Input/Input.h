#pragma once

#include "Graphics/Window/Window.h"

namespace GameEngine
{
	class KeyInput
	{
	public:
		static bool isKeyPressed(Window window, int keycode);
		static bool isKeyReleased(Window window, int keycode);
	};

	class MouseInput
	{
	public:
		static bool isMouseButtonPressed(Window window, int button);
		static std::pair<float, float> getMousePos(Window window);
	};
}