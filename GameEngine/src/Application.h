#pragma once

#include "Graphics/Window/Window.h"
#include "Graphics/OpenGL/OpenGL.h"

#include "Logging/Log.h"

#include "Events/WindowEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include "Input/Input.h"

#include "Objects/Triangle.h"

#include "Camera/Camera.h"

class Application
{
public:
	Application();
	~Application();

	void run();
	void OnEvent(Event& e);

	bool OnWindowClose(WindowCloseEvent& e);
	bool OnKeyPressed(KeyPressedEvent& e);
	bool OnMouseButtonPressed(MousePressedEvent& e);
	bool OnMouseMoved(MouseMovedEvent& e);

private:
	bool m_Running = true;

	OpenGL* m_Renderer;
	Shader m_Shader;
	Camera camera;

	float m_lastXPos, m_lastYPos;
	bool firstMouse = true;
};