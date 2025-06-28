#include "gepch.h"
#include "Application.h"

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application::Application()
{
	Window::Init(Window::WindowProps());
	Window::SetEventCallback(BIND_EVENT_FN(OnEvent));

	m_lastXPos = Window::GetWidth() / 2;
	m_lastYPos = Window::GetHeight() / 2;

	m_Renderer = new OpenGL();

	m_Shader.CompileShaders();
	m_Shader.Activate();
}

Application::~Application()
{

}

void Application::run()
{
	Triangle triangle = Triangle(18);
	while (m_Running)
	{
		m_Renderer->Clear();
		triangle.Draw();

		//Rotation Input
		if (KeyInput::isKeyPressed(GLFW_KEY_Q))
		{
			triangle.Rotate(camera, 0.02f);
		}
		else if (KeyInput::isKeyPressed(GLFW_KEY_E))
		{
			triangle.Rotate(camera, -0.02f);
		}

		camera.Update();
		camera.SetCoordUniforms(m_Shader);
		Window::OnUpdate();
	}
}

void Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher = EventDispatcher(e);

	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
	dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(OnKeyPressed));
	dispatcher.Dispatch<MousePressedEvent>(BIND_EVENT_FN(OnMouseButtonPressed));
	dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(OnMouseMoved));

	//INFO(e.toString());
}

bool Application::OnWindowClose(WindowCloseEvent& e)
{
	m_Running = false;
	return true;
}

bool Application::OnKeyPressed(KeyPressedEvent& e)
{
	return true;
}

bool Application::OnMouseButtonPressed(MousePressedEvent& e)
{
	if (e.getButton() == GLFW_MOUSE_BUTTON_1)
	{
		Window::LockMouse();
		glfwSetInputMode(Window::m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	return true;
}

bool Application::OnMouseMoved(MouseMovedEvent& e)
{
	//INFO(std::to_string(e.getX()) + std::string(", ") + std::to_string(e.getY()));

	if(firstMouse)
	{
		m_lastXPos = e.getX();
		m_lastYPos = e.getY();
		firstMouse = false;
	}

	float xOffset = e.getX() - m_lastXPos;
	float yOffset = e.getY() - m_lastYPos;

	m_lastXPos = e.getX();
	m_lastYPos = e.getY();

	camera.ProcessMouseMovement(xOffset, yOffset);

	TRACE(std::to_string(xOffset) + std::string(", ") + std::to_string(yOffset));
	return true;
}