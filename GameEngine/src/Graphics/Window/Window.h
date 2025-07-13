#pragma once

#include "Events/Event.h"

class Window
{
public:
	using EventCallbackFn = std::function<void(Event&)>;

	struct WindowData
	{
		std::string title;
		uint32_t width, height;
		bool VSync;

		EventCallbackFn EventCallback;
	};

	struct WindowProps
	{
		const std::string title;
		unsigned int width, height;

		WindowProps(const std::string& title = "Game Engine", unsigned int width = 1280, unsigned int height = 720)
			: title(title), width(width), height(height) {}
	};

	Window();
	Window(WindowProps props);

	void OnUpdate();

	inline unsigned int GetWidth() { return m_Data.width; }
	inline unsigned int GetHeight() { return m_Data.height; }
	inline GLFWwindow* getWindow() { return m_Window; }

	inline void SetEventCallback(const EventCallbackFn& callback)  { m_Data.EventCallback = callback; }
	void SetVSync(bool enabled);
	bool IsVSync();
	
	void LockMouse();
	void UnlockMouse();
	bool isLocked();

private:
	void Shutdown();
	void Init(const WindowProps& props);

	GLFWwindow* m_Window;
	WindowData m_Data;

	bool m_isLocked = false;
};	