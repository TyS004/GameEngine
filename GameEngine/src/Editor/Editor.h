#pragma once

#include "UIElements/UIElement.h"
#include "Graphics/Window/Window.h"
#include "Objects/Object.h"
#include "UIElements/Viewport.h"
#include "Graphics/Renderer/Renderer.h"

namespace GameEngine
{
	class Editor
	{
	public:
		Editor();
		Editor(Window* m_Window, Renderer* renderer);
		~Editor();

		void CreateUIElements();

		void StartFrame();
		void EndFrame();
		void Update();

		Viewport* CreateViewport(const char* label);
		Viewport* GetViewportByLabel(const std::string& label);

		void OnImGuiSliderChanged(const UIElement& element);
		void OnImGuiButtonPressed(const UIElement& element);
		void OnImGuiViewportResized();

		ImVec2 GetViewportSize();

	private:
		const uint32_t STARTINGVIEWPORTS = 5;
		const float UI_FONT_SIZE = 22.0f;
		const uint32_t IMGUI_WINDOW_WIDTH_BUFFER = 5;

		ImGuiStyle m_UIStyle;

		std::vector<Viewport*> m_viewports;
		uint32_t m_currentViewport = 0;

		std::unordered_map<std::string, float> m_SliderValues;
		
		ImVec2 m_viewportSize;

		Window* m_currentWindow;
		Renderer* m_currentRenderer;

		bool m_firstResize = true;
	};
}