#include "gepch.h"
#include "Application.h"

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application::Application()
{
	Window::Init(Window::WindowProps());
	Window::SetEventCallback(BIND_EVENT_FN(OnEvent));

	m_Renderer = new OpenGL();

	//Creating Triangle Buffers Temporary//
	m_Renderer->CreateBuffers();

}

Application::~Application()
{

}

void Application::run()
{
	while (m_Running)
	{
		m_Renderer->Clear();
		m_Renderer->DrawTriangle();
		m_Renderer->OnUpdate(glm::mat4(1.0f));
		Window::OnUpdate();
	}
}

void Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher = EventDispatcher(e);

	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
	dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(OnKeyPressed));

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