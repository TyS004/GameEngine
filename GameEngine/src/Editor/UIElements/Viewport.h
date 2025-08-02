#pragma once
#include "UIElement.h"

namespace GameEngine
{
	class Viewport
	{
	public:
		Viewport();
		Viewport(const std::string& label);
		~Viewport();

		bool Begin();
		void End();

		Slider* CreateSlider(const std::string& label, const UIEventFn& callback);
		Button* CreateButton(const std::string& label, const UIEventFn& callback);
		void InsertImage();

		void AddText();

		UIElement* GetElementByName(const std::string& name) const;

		std::string GetLabel();

		void Update();
	private:
		std::vector<UIElement*> m_elements;
		std::string m_label;
	};
}