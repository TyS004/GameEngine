#pragma once

#include "Event.h"

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

private:
	EventType m_type;

	int m_xOffset, m_yOffset;
};