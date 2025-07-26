#pragma once

#include "Core.h"

#include "Graphics/Window/Window.h"
#include "Graphics/Renderer/Renderer.h"

#include "Logging/Log.h"

#include "Events/WindowEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include "Input/Input.h"

#include "Objects/Object.h"

#include "Camera/Camera.h"

#include "Math/Math.h"

#include "Editor/UIElements/UIElement.h"
#include "Editor/Editor.h"

#include "Graphics/Buffer/Texture.h"
#include "Graphics/Buffer/FBO.h"
#include "Graphics/Buffer/RBO.h"

namespace GameEngine
{
	static const float START_WINDOW_WIDTH = 1980.0f;
	static const float START_WINDOW_HEIGHT = 1080.0f;

	class GE_API Application
	{
	public:
		Application();
		~Application();

		virtual void Run();
		void DrawObjects();
		void UpdateWindows();
		void OnEvent(Event& e);

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnMouseButtonPressed(MousePressedEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		static std::vector<Window*> m_Windows;
		static std::vector<Object*> m_Objects;

		static uint32_t m_ActiveWindow;
		static uint32_t m_SelectedObject;

	private:
		bool m_Running = true;

		Renderer* m_Renderer;
		Shader* m_Shader;
		Camera* m_Camera;
		Editor* m_Editor;

		std::unordered_map<std::string, float> m_SliderValues;

		float m_lastXPos, m_lastYPos;
		bool firstMouse = true;

		float m_viewportWidth = START_WINDOW_WIDTH;
		float m_viewportHeight = START_WINDOW_HEIGHT;
	};

	Application* CreateApplication();
}