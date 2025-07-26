#include "gepch.h"

#include "Editor.h"
#include "Application.h"

#define BIND_UIEVENT_FN(x) std::bind(&Editor::x, this, std::placeholders::_1)

namespace GameEngine
{
	Editor::Editor()
	{

	}

	Editor::Editor(Window* window, Renderer* renderer)
	{
		m_currentWindow = window;
		m_currentRenderer = renderer;
		m_viewportSize = ImVec2(START_WINDOW_WIDTH, START_WINDOW_HEIGHT);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(m_currentWindow->getWindow(), true);
		ImGui_ImplOpenGL3_Init();

		m_UIStyle = ImGui::GetStyle();

		ImGuiIO& m_io = ImGui::GetIO();
		m_io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		m_io.Fonts->AddFontFromFileTTF("assets/fonts/OpenSans-SemiBold.ttf", UI_FONT_SIZE);
		//m_io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();

		m_viewports.reserve(STARTINGVIEWPORTS);

		CreateUIElements();
	}

	void Editor::CreateUIElements()
	{
		Viewport* entitiesViewport = CreateViewport("Entities");
		Viewport* fileManagerViewport = CreateViewport("File Manager");
		Viewport* mainViewport = CreateViewport("Properties");
		Viewport* sceneViewport = CreateViewport("Viewport");

		Slider* xPos = mainViewport->CreateSlider("X", BIND_UIEVENT_FN(OnImGuiSliderChanged));
		Slider* yPos = mainViewport->CreateSlider("Y", BIND_UIEVENT_FN(OnImGuiSliderChanged));
		Slider* zPos = mainViewport->CreateSlider("Z", BIND_UIEVENT_FN(OnImGuiSliderChanged));

		Button* spawnButton = mainViewport->CreateButton("Spawn Object", BIND_UIEVENT_FN(OnImGuiButtonPressed));
	}

	Editor::~Editor()
	{

	}

	void Editor::StartFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (!m_firstResize)
		{
			m_viewportSize = ImGui::GetContentRegionAvail();
			m_currentRenderer->ResizeViewport(m_viewportSize.x, m_viewportSize.y);
			m_firstResize = false;
		}
	}

	void Editor::EndFrame()
	{
		if (!m_viewports.empty())
		{
			for (Viewport* viewport : m_viewports)
			{
				viewport->End();
			}
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& m_io = ImGui::GetIO();
		if (m_io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
	}

	Viewport* Editor::CreateViewport(const char* label)
	{
		Viewport* viewport = new Viewport(label);
		m_viewports.emplace_back(viewport);
		return viewport;
	}

	Viewport* Editor::GetViewportByLabel(const std::string& label)
	{
		for (Viewport* viewport : m_viewports)
		{
			if (viewport->GetLabel() == label)
			{
				return viewport;
			}
		}
		return nullptr;
	}

	void Editor::Update()
	{
		for (Viewport* viewport : m_viewports)
		{
			viewport->Update();
		}

		ImVec2 temp = m_viewportSize;
		m_viewportSize = ImGui::GetContentRegionAvail();
		if ((temp.x != m_viewportSize.x) || (temp.y != m_viewportSize.y))
		{
			OnImGuiViewportResized();
		}

		//ImGui Window Doesnt Fully take up the window space for some reason so need extra buffer
		ImGui::SetNextWindowSize(ImVec2(m_currentWindow->GetWidth() + IMGUI_WINDOW_WIDTH_BUFFER, m_currentWindow->GetHeight()));
		ImGui::Image(m_currentRenderer->GetFBOTexture().GetID(), ImVec2(m_viewportSize.x, m_viewportSize.y), ImVec2(0, 1), ImVec2(1, 0));
	}

	void Editor::OnImGuiSliderChanged(const UIElement& element)
	{
		const Slider& slider = dynamic_cast<const Slider&>(element);
		m_SliderValues[slider.GetName()] = slider.GetData();

		Object* currentObj = GameEngine::Application::m_Objects[0];

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

	void Editor::OnImGuiButtonPressed(const UIElement& element)
	{
		const Button& button = dynamic_cast<const Button&>(element);
		GameEngine::Application::m_Objects.emplace_back(new Object(m_SliderValues["X"], m_SliderValues["Y"], m_SliderValues["Z"]));
	}

	void Editor::OnImGuiViewportResized()
	{
		//renderer->ResizeViewport(m_viewportSize.x, m_viewportSize.y);
	}
	
	ImVec2 Editor::GetViewportSize()
	{
		return m_viewportSize;
	}
}