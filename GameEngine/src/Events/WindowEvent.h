#pragma once

#include "Event.h"

namespace GameEngine
{
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent()
			: m_type(EventType::WindowCloseEvent) {}

		EventType getType() const override { return m_type; }
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "WindowCloseEvent";
			return ss.str();
		}

		inline static EventType getStaticType() { return EventType::WindowCloseEvent; }

	private:
		EventType m_type;
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int xOffset, int yOffset)
			: m_type(EventType::WindowResizeEvent), m_xOffset(xOffset), m_yOffset(yOffset) {}

		EventType getType() const override { return m_type; }
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: (" << m_xOffset << ", " << m_yOffset << ")";
			return ss.str();
		}

		inline static EventType getStaticType() { return EventType::WindowResizeEvent; }

		inline uint32_t getWidth() { return m_xOffset; }
		inline uint32_t getHeight() { return m_yOffset; }

	private:
		EventType m_type;

		uint32_t m_xOffset, m_yOffset;
	};
}