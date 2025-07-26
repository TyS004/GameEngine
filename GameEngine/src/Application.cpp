#include "gepch.h"

#include "Application.h"

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace GameEngine
{
	std::vector<Window*> Application::m_Windows;
	std::vector<Object*> Application::m_Objects;

	uint32_t Application::m_ActiveWindow = 0;
	uint32_t Application::m_SelectedObject = 0;

	Application::Application()
	{
		Log::Init();

		//Window Init
		m_Windows.reserve(2);
		m_Windows.push_back(new Window(Window::WindowProps("GameEngine", START_WINDOW_WIDTH, START_WINDOW_HEIGHT)));
		m_Windows[m_ActiveWindow]->SetEventCallback(BIND_EVENT_FN(OnEvent));
		m_Windows[m_ActiveWindow]->LockMouse();

		m_lastXPos = 0.0f;
		m_lastYPos = 0.0f;

		m_Renderer = new Renderer();

		m_Shader = new Shader();
		m_Shader->CompileShaders();

		m_Camera = new Camera();

		m_Editor = new Editor(m_Windows[m_ActiveWindow], m_Renderer);

		m_Objects.reserve(5);
	}

	Application::~Application()
	{
		delete m_Renderer;
		delete m_Camera;
		delete m_Shader;
		delete m_Editor;

		for (Object* obj : m_Objects)
		{
			delete obj;
		}
	}

	void Application::Run()
	{
		//Needs to be in Sandbox as GameEngine::Renderer::LoadTexture("assets/textures/brick-3.png");
		Texture blockTexture("assets/textures/brick-3.png");

		//TEMP Object creation as GameEngine::Renderer::DrawCube();
		m_Objects.push_back(new Object(0.0f, 0.0f, 0.0f));
		glViewport(0, 0, START_WINDOW_WIDTH, START_WINDOW_HEIGHT);

		//Main Loop
		while (m_Running)
		{

			//ECS for(Mesh* mesh : Meshes)
			//	  {
			//	     Render(Mesh)
			//    }
			// 

			//1st Pass Rendering Objects to FBO
			m_Renderer->GetFBO().Bind();
			blockTexture.Bind();

			m_Shader->Activate();
			m_Shader->setTextureUniform(0);
			m_Renderer->Clear(0.0f, 0.0f, 0.0f, 1.0f);
			m_Camera->Update(*m_Windows[m_ActiveWindow], m_viewportWidth, m_viewportHeight);
			m_Shader->setUniformMat4f(m_Camera->GetViewMatrix(), "view");
			m_Shader->setUniformMat4f(m_Camera->GetProjectionMatrix(), "projection");
			DrawObjects();

			blockTexture.Unbind();
			m_Renderer->GetFBO().Unbind();

			////Upload Texture to ImGui Viewport 
			m_Renderer->Clear(0.5f, 0.5f, 0.5f, 1.0f);

			//ImGui Render Loop
			m_Editor->StartFrame();
			m_Editor->Update();
			m_Editor->EndFrame();

			UpdateWindows();
		}
	}

	void Application::DrawObjects()
	{
		for (Object* object : m_Objects)
		{
			m_Shader->setUniformMat4f(object->GetModelMatrix(), "model");
			object->Draw();
		}
	}

	void Application::UpdateWindows()
	{
		for (Window* window : m_Windows)
		{
			window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher = EventDispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(OnKeyPressed));
		dispatcher.Dispatch<MousePressedEvent>(BIND_EVENT_FN(OnMouseButtonPressed));
		dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(OnMouseMoved));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnKeyPressed(KeyPressedEvent& e)
	{
		if (e.getKeycode() == GLFW_KEY_ESCAPE && !m_Windows[m_ActiveWindow]->isLocked())
		{
			m_Windows[m_ActiveWindow]->LockMouse();
		}
		else if (e.getKeycode() == GLFW_KEY_ESCAPE)
		{
			m_Windows[m_ActiveWindow]->UnlockMouse();
			firstMouse = true;
		}

		return true;
	}

	bool Application::OnMouseButtonPressed(MousePressedEvent& e)
	{
		return true;
	}

	bool Application::OnMouseMoved(MouseMovedEvent& e)
	{
		if (firstMouse)
		{
			m_lastXPos = (float)e.getX();
			m_lastYPos = (float)e.getY();
			firstMouse = false;
		}

		float xOffset = e.getX() - m_lastXPos;
		float yOffset = e.getY() - m_lastYPos;

		m_lastXPos = (float)e.getX();
		m_lastYPos = (float)e.getY();

		if (m_Windows[m_ActiveWindow]->isLocked())
		{
			m_Camera->ProcessMouseMovement(xOffset, yOffset);
		}

		//TRACE(std::to_string(e.getX()) + " " + std::to_string(e.getY()));
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		int width, height;
		glfwGetWindowSize(m_Windows[m_ActiveWindow]->getWindow(), &width, &height);

		m_Renderer->ResizeViewport(m_Editor->GetViewportSize().x, m_Editor->GetViewportSize().y);

		return true;
	}
}