#include "gepch.h"
#include "UI.h"

UI::UI()
{

}

UI::UI(Window& window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
	ImGui_ImplOpenGL3_Init();

	ImGuiIO& m_io = ImGui::GetIO();
	m_io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	//m_io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	m_viewports.reserve(STARTINGVIEWPORTS);
}

UI::~UI()
{
	 
}

void UI::StartFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void UI::EndFrame()
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

Viewport* UI::CreateViewport(const char* label)
{
	Viewport* viewport = new Viewport(label);
	m_viewports.emplace_back(viewport);
	return viewport;
}

Viewport* UI::GetViewportByLabel(const std::string& label)
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

void UI::Update()
{
	for (Viewport* viewport : m_viewports)
	{
		viewport->Update();
	}
}