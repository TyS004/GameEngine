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

		void OnImGuiSliderChanged(const UIElement& element);
		void OnImGuiButtonPressed(const UIElement& element);
		void OnImGuiViewportResized();

		ImVec2 GetViewportSize();

	private:
		const uint32_t STARTINGVIEWPORTS = 5;
		const uint32_t IMGUI_WINDOW_WIDTH_BUFFER = 5;
		const float UI_FONT_SIZE = 22.0f;

		ImGuiStyle m_UIStyle;

		std::unordered_map<std::string, float> m_SliderValues;
		
		ImVec2 m_viewportSize;

		Window* m_currentWindow;
		Renderer* m_currentRenderer;

		Viewport* m_entitiesViewport;
		Viewport* m_fileManagerViewport;
		Viewport* m_mainViewport;
		Viewport* m_sceneViewport;

		Slider* m_xPos;
		Slider* m_yPos;
		Slider* m_zPos;

		Button* m_spawnButton;

		bool m_firstResize = true;
	};
}