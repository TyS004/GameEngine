#include "gepch.h"
#include "Application.h"

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application::Application()
{
	m_Windows = new Window*[numWindows]();
	m_Windows[0] = new Window();
	m_Windows[0]->SetEventCallback(BIND_EVENT_FN(OnEvent));
	m_Windows[0]->LockMouse();

	m_lastXPos = m_Windows[0]->GetWidth() / 2;
	m_lastYPos = m_Windows[0]->GetHeight() / 2;

	m_Renderer = new OpenGL();

	m_Shader = new Shader();
	m_Shader->CompileShaders();
	m_Shader->Activate();

	m_Camera = new Camera();

	m_Objects = new Triangle*[numObjects];
	m_Objects[0] = new Triangle(0.0f, 0.0f, 0.0f);

	Math::Matrix4D matrix = Math::Matrix4D(1.0f);
	//INFO(matrix);

	bool open;
	//ImGui::Begin("Level Editor", &open, ImGuiWindowFlags_MenuBar);
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(m_Windows[0]->getWindow(), true);
	ImGui_ImplOpenGL3_Init();
}

Application::~Application()
{
	for (int i = 0; i < numWindows; ++i)
	{
		delete m_Windows[i];
	}
	for (int i = 0; i < numObjects; ++i)
	{
		delete m_Objects[i];
	}
	delete m_Renderer;
	delete m_Camera;
	delete m_Shader;
	
}

void Application::run()
{
	while (m_Running)
	{
		m_Renderer->Clear();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame(); 
		ImGui::NewFrame();
		ImGui::Begin("Level Editor");

		bool isClicked = false;
		isClicked = ImGui::Button("Spawn Object");

		if (isClicked)
		{
			m_Objects[numObjects++] = new Triangle(5.0f, 5.0f, 5.0f);
			INFO("Spawned Object");
		}

		m_Camera->Update(*m_Windows[0]);
		m_Camera->SetCoordUniforms(*m_Shader);

		for (int i = 0; i < numObjects; ++i)
		{
			m_Objects[i]->setUniform(*m_Shader);
			m_Objects[i]->Draw();
		}

		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		for (int i = 0; i < numWindows; ++i)
		{
			m_Windows[i]->OnUpdate();
		}
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
	if (e.getKeycode() == GLFW_KEY_ESCAPE && !m_Windows[0]->isLocked())
	{
		m_Windows[0]->LockMouse();
	}
	else if(e.getKeycode() == GLFW_KEY_ESCAPE)
	{
		m_Windows[0]->UnlockMouse();
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

	if (m_Windows[0]->isLocked())
	{
		m_Camera->ProcessMouseMovement(xOffset, yOffset);
	}
	//TRACE(std::to_string(xOffset) + std::string(", ") + std::to_string(yOffset));
	return true;
}