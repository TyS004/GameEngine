#include "gepch.h"
#include "Application.h"

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application::Application()
{
	//Window Init
	m_Windows.reserve(2);
	m_Windows.push_back(new Window(Window::WindowProps("GameEngine", 800, 600)));
	m_Windows[m_ActiveWindow]->SetEventCallback(BIND_EVENT_FN(OnEvent));
	m_Windows[m_ActiveWindow]->LockMouse();

	m_lastXPos = 0.0f;
	m_lastYPos = 0.0f;

	m_Renderer = new OpenGL();

	m_Shader = new Shader();
	m_Shader->CompileShaders();
	m_Shader->Activate();

	m_Camera = new Camera();

	m_UI = new UI(*m_Windows[m_ActiveWindow]);

	//Reserving for 5 Objs rn & just create one at (0, 0, 0)
	m_Objects.reserve(5);
	m_Objects.push_back(new Object(0.0f, 0.0f, 0.0f));
	m_Objects[m_SelectedObject]->setUniform(*m_Shader);
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
	Viewport* mainViewport = m_UI->CreateViewport("Viewport");

	Slider* xPos = mainViewport->CreateSlider("X Position", BIND_EVENT_FN(OnImGuiSliderChanged));
	Slider* yPos = mainViewport->CreateSlider("Y Position", BIND_EVENT_FN(OnImGuiSliderChanged));
	Slider* zPos = mainViewport->CreateSlider("Z Position", BIND_EVENT_FN(OnImGuiSliderChanged));

	Button* spawnButton = mainViewport->CreateButton("Spawn Object", BIND_EVENT_FN(OnImGuiButtonPressed));
	
	Texture texture("assets/textures/brick-3.png");
	texture.Bind();
	m_Shader->setTextureUniform();

	//Main Loop
	while (m_Running)
	{
		m_Renderer->Clear();

		m_UI->StartFrame();
		m_UI->Update();

		m_Camera->Update(*m_Windows[m_ActiveWindow]);
		m_Camera->SetCoordUniforms(*m_Shader);

		DrawObjects();

		m_UI->EndFrame();

		UpdateWindows();
	}
}

void Application::DrawObjects()
{
	for (Object* object : m_Objects)
	{
		object->setUniform(*m_Shader);
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

	//INFO(e.toString());
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
	return true;
}

bool Application::OnWindowResize(WindowResizeEvent& e)
{
	int width, height;
	glfwGetWindowSize(m_Windows[m_ActiveWindow]->getWindow(), &width, &height);
	INFO("Window Resized");
	INFO(std::to_string(width) + ", " +  std::to_string(height));

	return true;
}

void Application::OnImGuiSliderChanged(const UIElement& element)
{
	const Slider& slider = dynamic_cast<const Slider&>(element);
	m_SliderValues[slider.GetName()] = slider.GetData();

	Object* currentObj = m_Objects[m_SelectedObject];

	if (slider.GetName() == "X Position")
	{
		currentObj->Translate(slider.GetData(), currentObj->getTransform().y, currentObj->getTransform().z, *m_Shader);
		INFO(slider.GetData());
	}
	else if (slider.GetName() == "Y Position")
	{
		currentObj->Translate(currentObj->getTransform().x, slider.GetData(), currentObj->getTransform().z, *m_Shader);
	}
	else if (slider.GetName() == "Z Position")
	{
		currentObj->Translate(currentObj->getTransform().x, currentObj->getTransform().y, slider.GetData(), *m_Shader);
	}
}

void Application::OnImGuiButtonPressed(const UIElement& element)
{
	const Button& button = dynamic_cast<const Button&>(element);
	m_Objects.emplace_back(new Object(m_SliderValues["X Position"], m_SliderValues["Y Position"], m_SliderValues["Z Position"]));
}