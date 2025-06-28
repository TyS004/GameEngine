#pragma once

#include "Events/Event.h"

class Window
{
public:
	using EventCallbackFn = std::function<void(Event&)>;

	struct WindowData
	{
		std::string title;
		unsigned int width, height;
		bool VSync;

		EventCallbackFn EventCallback;
	};

	static GLFWwindow* m_Window;
	static WindowData m_Data;

	static bool isMouseLocked;

	struct WindowProps
	{
		const std::string title;
		unsigned int width, height;

		WindowProps(const std::string& title = "Game Engine", unsigned int width = 800, unsigned int height = 600)
			: title(title), width(width), height(height) {}
	};

	static void OnUpdate();

	static void Init(const WindowProps& props);

	inline static unsigned int GetWidth() { return m_Data.width; }
	inline static unsigned int GetHeight() { return m_Data.height; }

	inline static GLFWwindow* getWindow() { return m_Window; }

	inline static void SetEventCallback(const EventCallbackFn& callback)  { m_Data.EventCallback = callback; }
	static void SetVSync(bool enabled);
	static bool IsVSync();
	
	static void SetCursorMode(GLuint mode);
	static void LockMouse();

private:
	static void Shutdown();
};	