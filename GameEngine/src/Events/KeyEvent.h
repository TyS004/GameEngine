#pragma once

#include "Event.h"

class KeyPressedEvent : public Event
{
public:
	KeyPressedEvent(int keycode, int repeats)
		: m_type(EventType::KeyPressedEvent), m_keycode(keycode), m_repeats(repeats) {}

	EventType getType() const override { return m_type; }
	std::string toString() const override
	{
		std::stringstream ss;
		ss << "KeyPressedEvent: " << m_keycode;
		return ss.str();
	}

	inline static EventType getStaticType() { return EventType::KeyPressedEvent; }

private:
	EventType m_type;
	int m_keycode, m_repeats;
};

class KeyReleasedEvent : public Event
{
public:
	KeyReleasedEvent(int keycode)
		: m_type(EventType::KeyReleasedEvent), m_keycode(keycode) {}

	EventType getType() const override { return m_type; }
	std::string toString() const override
	{
		std::stringstream ss;
		ss << "KeyReleasedEvent: " << m_keycode;
		return ss.str();
	}

	inline static EventType getStaticType() { return EventType::KeyReleasedEvent; }

private:
	EventType m_type;
	int m_keycode;
};