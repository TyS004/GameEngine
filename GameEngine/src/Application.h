#pragma once

#include "Graphics/Window/Window.h"
#include "Graphics/OpenGL/OpenGL.h"

#include "Logging/Log.h"

#include "Events/WindowEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include "Input/Input.h"

class Application
{
public:
	Application();
	~Application();

	void run();
	void OnEvent(Event& e);

	bool OnWindowClose(WindowCloseEvent& e);
	bool OnKeyPressed(KeyPressedEvent& e);

private:
	bool m_Running = true;

	OpenGL* m_Renderer;
};