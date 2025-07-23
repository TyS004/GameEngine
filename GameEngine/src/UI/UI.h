#pragma once

#include "UIElements/UIElement.h"
#include "Graphics/Window/Window.h"
#include "Objects/Object.h"
#include "UIElements/Viewport.h"

namespace GameEngine
{
	class UI
	{
	public:
		UI();
		UI(Window& m_Window);
		~UI();

		void StartFrame();
		void EndFrame();
		void Update();

		Viewport* CreateViewport(const char* label);

		Viewport* GetViewportByLabel(const std::string& label);

	private:
		const uint32_t STARTINGVIEWPORTS = 5;

		std::vector<Viewport*> m_viewports;
		uint32_t m_currentViewport = 0;
	};
}