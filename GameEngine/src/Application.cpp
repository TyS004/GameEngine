#include "gepch.h"
#include "Application.h"

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application::Application()
{
	//Window Init
	m_Windows.reserve(2);
	m_Windows.push_back(new Window(Window::WindowProps("GameEngine", START_WINDOW_WIDTH, START_WINDOW_HEIGHT)));
	m_Windows[m_ActiveWindow]->SetEventCallback(BIND_EVENT_FN(OnEvent));
	m_Windows[m_ActiveWindow]->LockMouse();

	m_lastXPos = 0.0f;
	m_lastYPos = 0.0f;

	m_Renderer = new OpenGL();

	m_Shader = new Shader();
	m_Shader->CompileShaders();

	m_Camera = new Camera();

	m_UI = new UI(*m_Windows[m_ActiveWindow]);

	m_Objects.reserve(5);
}

Application::~Application()
{
	delete m_Renderer;
	delete m_Camera;
	delete m_Shader;
}

void Application::Run()
{
	//IMGUI Element Creation
	Viewport* mainViewport = m_UI->CreateViewport("Transform");
	Viewport* sceneViewport = m_UI->CreateViewport("Viewport");

	Slider* xPos = mainViewport->CreateSlider("X", BIND_EVENT_FN(OnImGuiSliderChanged));
	Slider* yPos = mainViewport->CreateSlider("Y", BIND_EVENT_FN(OnImGuiSliderChanged));
	Slider* zPos = mainViewport->CreateSlider("Z", BIND_EVENT_FN(OnImGuiSliderChanged));

	Button* spawnButton = mainViewport->CreateButton("Spawn Object", BIND_EVENT_FN(OnImGuiButtonPressed));

	Texture frameTexture(m_Windows[m_ActiveWindow]->GetWidth(), m_Windows[m_ActiveWindow]->GetHeight());
	FBO FBO1(frameTexture, m_Windows[m_ActiveWindow]->GetWidth(), m_Windows[m_ActiveWindow]->GetHeight());
	RBO RBO1(FBO1, m_Windows[m_ActiveWindow]->GetWidth(), m_Windows[m_ActiveWindow]->GetHeight());

	Texture blockTexture("assets/textures/brick-3.png");

	m_Objects.push_back(new Object(0.0f, 0.0f, 0.0f));
	m_Shader->setUniformMat4f(m_Objects[m_SelectedObject]->GetModelMatrix(), "model");
	
	glViewport(0, 0, START_WINDOW_WIDTH, START_WINDOW_HEIGHT);

	//Main Loop
	while (m_Running)
	{
		//1st Pass Rendering Objects to FBO
		FBO1.Bind();
		blockTexture.Bind();

		m_Shader->Activate();
		m_Shader->setTextureUniform(0);
		m_Renderer->Clear();
		m_Camera->Update(*m_Windows[m_ActiveWindow], m_viewportWidth, m_viewportHeight);
		m_Shader->setUniformMat4f(m_Camera->GetViewMatrix(), "view");
		m_Shader->setUniformMat4f(m_Camera->GetProjectionMatrix(), "projection");
		DrawObjects();

		blockTexture.Unbind();
		FBO1.Unbind();

		////2nd Pass FBO -> Quad
		m_Renderer->Clear();
		//m_Renderer->RenderQuad(frameTexture);

		//ImGui Render Loop
		m_UI->StartFrame();
		m_UI->Update();
		
		ImVec2 wsize = ImGui::GetWindowSize();
		ImVec2 pos = ImGui::GetCursorScreenPos();

		auto viewportSize = ImGui::GetContentRegionAvail();
		m_viewportWidth = viewportSize.x;
		m_viewportHeight = viewportSize.y;

		ImGui::Image(frameTexture.getID(), wsize, ImVec2(0, 1), ImVec2(1, 0));
		m_UI->EndFrame();

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
	else if(e.getKeycode() == GLFW_KEY_ESCAPE)
	{
		m_Windows[m_ActiveWindow]->UnlockMouse();
		firstMouse = true;
	}

	/*if (e.getKeycode() == GLFW_KEY_Y)
	{
		ImVec2 wsize = ImGui::GetWindowSize();
		ImVec2 pos = ImGui::GetCursorScreenPos();

		auto viewportSize = ImGui::GetContentRegionAvail();

		INFO("ImGui Scene Size: " + std::to_string(wsize.x) + " " + std::to_string(wsize.y));
		INFO("ImGui Scene Position: " + std::to_string(pos.x) + " " + std::to_string(pos.y));
		TRACE("Viewport: " + std::to_string(viewportSize.x) + " " + std::to_string(viewportSize.y));
	}*/

	return true;
}

bool Application::OnMouseButtonPressed(MousePressedEvent& e)
{
	return true;
}

bool Application::OnMouseMoved(MouseMovedEvent& e)
{
	if(firstMouse)
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
	INFO("Window Resized");
	INFO(std::to_string(width) + ", " +  std::to_string(height));

	//m_Renderer->ResizeViewport(e.getWidth(), e.getHeight());
	//ImGui::SetWindowSize(ImVec2(e.getWidth(), e.getHeight()));

	return true;
}

void Application::OnImGuiSliderChanged(const UIElement& element)
{
	const Slider& slider = dynamic_cast<const Slider&>(element);
	m_SliderValues[slider.GetName()] = slider.GetData();

	Object* currentObj = m_Objects[m_SelectedObject];

	if (slider.GetName() == "X")
	{
		currentObj->Translate(slider.GetData(), currentObj->getTransform().y, currentObj->getTransform().z);
		INFO(slider.GetData());
	}
	else if (slider.GetName() == "Y")
	{
		currentObj->Translate(currentObj->getTransform().x, slider.GetData(), currentObj->getTransform().z);
		INFO(slider.GetData());
	}
	else if (slider.GetName() == "Z")
	{
		currentObj->Translate(currentObj->getTransform().x, currentObj->getTransform().y, slider.GetData());
		INFO(slider.GetData());
	}
}

void Application::OnImGuiButtonPressed(const UIElement& element)
{
	const Button& button = dynamic_cast<const Button&>(element);
	m_Objects.emplace_back(new Object(m_SliderValues["X"], m_SliderValues["Y"], m_SliderValues["Z"]));

	TRACE(m_SliderValues["X"]);
	TRACE(m_SliderValues["Y"]);
	TRACE(m_SliderValues["Z"]);
}