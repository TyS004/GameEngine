#include "gepch.h"
#include "Viewport.h"

namespace GameEngine
{
	Viewport::Viewport()
	{
		m_elements.reserve(5);
	}

	Viewport::Viewport(const std::string& label)
	{
		m_elements.reserve(5);
		m_label = label;
	}

	Viewport::~Viewport()
	{

	}

	void Viewport::Begin()
	{
		ImGui::Begin(m_label.c_str(), nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	}

	void Viewport::End()
	{
		ImGui::End();
	}

	Slider* Viewport::CreateSlider(const std::string& label, const UIEventFn& callback)
	{
		Slider* slider = new Slider(label, callback);
		m_elements.push_back(slider);

		return slider;
	}

	Button* Viewport::CreateButton(const std::string& label, const UIEventFn& callback)
	{
		Button* button = new Button(label, callback);
		m_elements.push_back(button);

		return button;
	}


	std::string Viewport::GetLabel()
	{
		return m_label;
	}

	UIElement* Viewport::GetElementByName(const std::string& name) const
	{
		for (UIElement* element : m_elements)
		{
			if (element->GetName() == name)
			{
				return element;
			}
		}
		return nullptr;
	}

	void Viewport::Update()
	{
		Begin();
		for (UIElement* element : m_elements)
		{
			element->Update();
		}
	}
}