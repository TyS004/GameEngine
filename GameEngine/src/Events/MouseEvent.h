#pragma once

#include "Event.h"

class MousePressedEvent : public Event
{
public:
	MousePressedEvent(int button)
		: m_type(EventType::MousePressedEvent), m_button(button) {}

	EventType getType() const override { return m_type; }
	int getButton() const { return m_button; }

	std::string toString() const override
	{
		std::stringstream ss;
		ss << "MousePressedEvent: " << m_button;
		return ss.str();
	}

	inline static EventType getStaticType() { return EventType::MousePressedEvent; }

private:
	EventType m_type;
	int m_button;
};

class MouseReleasedEvent : public Event
{
public:
	MouseReleasedEvent(int button)
		: m_type(EventType::MouseReleasedEvent), m_button(button) {}

	EventType getType() const override { return m_type; }
	int getButton() const { return m_button; }

	std::string toString() const override
	{
		std::stringstream ss;
		ss << "MouseReleasedEvent: " << m_button;
		return ss.str();
	}

	inline static EventType getStaticType() { return EventType::MouseReleasedEvent; }

private:
	EventType m_type;
	int m_button;
};

class MouseScrolledEvent : public Event
{
public:
	MouseScrolledEvent(float xOffset, float yOffset)
		: m_type(EventType::MouseScrolledEvent), m_xOffset(xOffset), m_yOffset(yOffset) {}

	EventType getType() const override { return m_type; }

	std::string toString() const override
	{
		std::stringstream ss;
		ss << "MouseScrolledEvent: " << m_xOffset << ", " << m_yOffset;
		return ss.str();
	}

	inline static EventType getStaticType() { return EventType::MouseScrolledEvent; }

private:
	EventType m_type;
	float m_xOffset, m_yOffset;
};

class MouseMovedEvent : public Event
{
public:
	MouseMovedEvent(int x, int y)
		: m_type(EventType::MouseMovedEvent), m_x(x), m_y(y) {}

	EventType getType() const override { return m_type; }

	int getX() const { return m_x; }
	int getY() const { return m_y; }

	std::string toString() const override
	{
		std::stringstream ss;
		ss << "MouseMovedEvent: (" << m_x << ", " << m_y << ")";
		return ss.str();
	}

	inline static EventType getStaticType() { return EventType::MouseMovedEvent; }

private:
	EventType m_type;
	unsigned int m_x, m_y;
};