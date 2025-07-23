#pragma once
#include "gepch.h"

namespace GameEngine
{
	enum class UIElementType
	{
		UI_ELEMENT_BUTTON, UI_ELEMENT_SLIDER
	};

	class UIElement
	{
	public:
		virtual ~UIElement() = default;

		virtual std::string GetName() const = 0;
		virtual UIElementType GetType() const = 0;

		virtual void Update() = 0;
	};

	using UIEventFn = std::function<void(const UIElement& element)>;

	class Slider : public UIElement
	{
	public:
		Slider(const std::string& name, const UIEventFn& callback)
			: m_name(name), m_data(0.0f), m_callback(callback) {}
		~Slider() {}

		float GetData() const { return m_data; }
		std::string GetName() const override { return m_name; }
		UIElementType GetType() const override { return UIElementType::UI_ELEMENT_SLIDER; }

		void SetData(const float& data) { m_data = data; }
		void SetCallback(const UIEventFn& callback) { m_callback = callback; }

		void Update() override
		{
			if (ImGui::SliderFloat(m_name.c_str(), &m_data, -5.0f, 5.0f))
			{
				m_callback(*this);
			}
		}

	private:
		float m_data;
		std::string m_name;

		UIEventFn m_callback;
	};

	class Button : public UIElement
	{
	public:
		Button(const std::string& label, const UIEventFn& callback)
			:m_name(label), m_callback(callback) {}
		~Button() {}

		std::string GetName() const override { return m_name; }
		UIElementType GetType() const override { return UIElementType::UI_ELEMENT_BUTTON; }

		void Update() override
		{
			m_isClicked = ImGui::Button("Spawn Object");
			if (m_isClicked)
			{
				m_callback(*this);
			}
		}

	private:
		bool m_isClicked = false;
		std::string m_name;

		UIEventFn m_callback;
	};
}