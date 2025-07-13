#include "gepch.h"

#include "Window.h"
#include "Logging/Log.h"

#include "Events/WindowEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

static bool s_GLFWIntialized = false;

static void GLFWErrorCallback(int error, const char* description)
{
	WARN("GLFW ERROR OCCURED!");
}

Window::Window()
{
	Init(WindowProps());
}

Window::Window(WindowProps props)
{
	Init(props);
}


void Window::Init(const WindowProps& props)
{
	m_Data.title = props.title;
	m_Data.width = props.width;
	m_Data.height = props.height;

	INFO("Creating Window");

	if (!s_GLFWIntialized)
	{
		int success = glfwInit();
		if (success == GLFW_FALSE) FATAL("Could Not Initalize GLFW!");
		glfwSetErrorCallback(GLFWErrorCallback);

		s_GLFWIntialized = true;
	}

	m_Window = glfwCreateWindow((int)props.width, (int)props.height, m_Data.title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window, &m_Data);
	SetVSync(true);

	//GLFW Callback Event Setting
	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		data.width = width;
		data.height = height;

		WindowResizeEvent event(width, height);
		data.EventCallback(event);
	});

	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		WindowCloseEvent event;
		data.EventCallback(event);
	});

	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				data.EventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, 1);
				data.EventCallback(event);
				break;
			}
		}
	});

	glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
			case GLFW_PRESS:
			{
				MousePressedEvent event(button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseReleasedEvent event(button);
				data.EventCallback(event);
				break;
			}
		}
	});

	glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		MouseScrolledEvent event((float)xOffset, (float)yOffset);
		data.EventCallback(event);
	});

	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		MouseMovedEvent event((float)xPos, (float)yPos);
		data.EventCallback(event);
	});
}

void Window::Shutdown()
{
	glfwDestroyWindow(m_Window);
} 

void Window::OnUpdate()
{
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

void Window::SetVSync(bool enabled)
{
	if (enabled)
	{
		glfwSwapInterval(1);
	}
	else
	{
		glfwSwapInterval(0);
	}
	m_Data.VSync = enabled;
}

bool Window::IsVSync()
{
	return Window::m_Data.VSync;
}

void Window::LockMouse()
{
	glfwSetInputMode(Window::m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	m_isLocked = true;
}

void Window::UnlockMouse()
{
	glfwSetInputMode(Window::m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	m_isLocked = false;
}

bool Window::isLocked()
{
	return m_isLocked;
}